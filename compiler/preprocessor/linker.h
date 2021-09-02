#include <dirent.h>

#include "path_analyser.h"

void insSubFil(FILE *subTmpPtr, FILE *dstFilPtr, FileInfo **curFile, char *fnlPth, char *srcPth, int rptColSft, int datColSft){

    FileInfo *subFilInf = checkFlags(subTmpPtr, fnlPth, 0); //An object that contains the sub-file info!

    printf("\n[Debug] [Sub] Mode: %c\n", subFilInf->mode);
    printf("[Debug] [Sub] Is Full: %d\n", subFilInf->isFull);
    printf("[Debug] [Sub] Current Line Content: %s\n", subFilInf->currLineCon);
    printf("[Debug] [Sub] Current Line Original Content: %s\n", subFilInf->currOLineCon);
    printf("[Debug] [Sub] Path: %s\n", subFilInf->path);

    if(subFilInf->mode == 'U'){ //This is neither a `.mur` file nor a `.lib.mur` file

        rpt(REPORT_CODE_ERROR, //This is an error
        REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
        MSG_PPC_LINKER_INCORRECTFILETYPE, //This is the custom error message (check /compiler/errors/messages.h)
        srcPth, //The source of this error
        (*curFile)->currLine, //The line of this error
        (*curFile)->currCol + rptColSft); //The column the error occurs

    }else{

        char *tmpSrcStr = malloc(sizeof(char)*(strlen(srcPth) + strlen(fnlPth) + 4));

        char *tmpDatStr = malloc(sizeof(char)*(strlen(fnlPth) + 26 + 3));

        sprintf(tmpDatStr, "%s <Zx%09X> <Zx%09X>", fnlPth, (*curFile)->currLine, (*curFile)->currCol + datColSft);

        int pthDatId = savDat(DATA_PATH, tmpDatStr);

        free(tmpDatStr);

        sprintf(tmpSrcStr, "<%cx%06X>@%s", DATA_PATH, pthDatId, srcPth);

        ppcRead(subFilInf, dstFilPtr, tmpSrcStr); //Let the preprocessor do its thing, again!

        free(tmpSrcStr);

    }

    fclose(subTmpPtr);

}

void rmvPrcSec(FileInfo **curFile, int *len, int *i, int stmIndx){

    int tmp = ++(*i) - stmIndx;

    shfStr((*curFile)->currLineCon, tmp);

    i = 0;
    *len = strlen((*curFile)->currLineCon);

    if(*len == 1)
        strcpy((*curFile)->currLineCon, FILLER_STRING_CHAR_TYP_STR);

    (*curFile)->currCol += tmp;
    (*curFile)->nextCol = (*curFile)->currCol;

}

void chkForPprFunc(FileInfo **curFile, FILE *dstFilPtr, char *srcPth){

    int len = strlen((*curFile)->currLineCon), inStr = 0, inChr = 0;

    for(int i = 0; i < len; i++){

        if((i - 1 != -1) ? (((*curFile)->currLineCon)[i - 1] != '\\') : 1) { //Look for the '\' char

            if(!inChr && ((*curFile)->currLineCon)[i] == '"') //String opening/closing
                inStr = !inStr;

            if(!inStr && ((*curFile)->currLineCon)[i] == '\'') //Char opening/closing
                inChr = !inChr;

        }

        int shdChk = !inStr && !inChr;

        if(shdChk && (*curFile)->mode == 'L'){ //The separate zone is not restricted to the root zone!

            if(i + 2 < len && ((*curFile)->currLineCon)[i] == '<' && ((*curFile)->currLineCon)[i + 1] == '<' && ((*curFile)->currLineCon)[i + 2] == '<'){

                //Start a seperate zone
                (*curFile)->isSptZon = 1;

                char *tmpStr = malloc(sizeof(char)*(28));

                sprintf(tmpStr, "<Zx%09X> <Zx%09X>", (*curFile)->currLine, i + (*curFile)->currCol);

                int tmpId = savDat(DATA_ZONE, tmpStr);

                sprintf((*curFile)->curZonId, "<%cx%06X>@", DATA_ZONE, tmpId);

                free(tmpStr);

                strcpy((*curFile)->currLineCon, FILLER_STRING_CHAR_TYP_STR);

                i = len;

            }

            if(i + 2 < len && ((*curFile)->currLineCon)[i] == '>' && ((*curFile)->currLineCon)[i + 1] == '>' && ((*curFile)->currLineCon)[i + 2] == '>'){

                //End a seperate zone
                (*curFile)->isSptZon = 0;

                strcpy((*curFile)->currLineCon, FILLER_STRING_CHAR_TYP_STR);

                i = len;

            }

        }
        
        if(shdChk && ((*curFile)->currLineCon)[i] == '{'){ //Beaware, a new zone opening has been detected!

            (*curFile)->curZon++;

        }else if(shdChk && ((*curFile)->currLineCon)[i] == '}'){  //Beaware, a new zone closing has been detected!

            (*curFile)->curZon--;

        }else if(shdChk && (*curFile)->curZon == 0 && (i == 0 || isspace(((*curFile)->currLineCon)[i - 1]) || ((*curFile)->currLineCon)[i - 1] == ';')){

            //You can start looking now!

            if(ENABLE_USING_STATEMENT && i + 5 < len &&
                ((*curFile)->currLineCon)[i] == 'u' &&
                ((*curFile)->currLineCon)[i + 1] == 's' &&
                ((*curFile)->currLineCon)[i + 2] == 'i' &&
                ((*curFile)->currLineCon)[i + 3] == 'n' &&
                ((*curFile)->currLineCon)[i + 4] == 'g' &&
                ((*curFile)->currLineCon)[i + 5] == ' '){

                //The "using" statement has been detected!
                writeLogLine("Preprocessor", 0, "A 'using' statement has been detected!", 1, (*curFile)->currLine, (*curFile)->currCol + i);

                int stmIndx = i, lokForNum = 1, isFsh = 0, pthLen = strlen(MUR_LIBRARIES_DIR) + 1;

                char *libPth = malloc(sizeof(char)*pthLen);
                strcpy(libPth, MUR_LIBRARIES_DIR);

                for(i += 6; i < len; i++){

                    if(((*curFile)->currLineCon)[i] == ';'){

                        isFsh = 1;
                        break;

                    }

                    if(!isspace(((*curFile)->currLineCon)[i])) {

                        if(lokForNum && isdigit(((*curFile)->currLineCon)[i])) { //Only accept names that start with letters

                            rpt(REPORT_CODE_ERROR, //This is an error
                            REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                            MSG_PPC_LINKER_USING_NODIGITSATSTART, //This is the custom error message (check /compiler/errors/messages.h)
                            srcPth, //The source of this error
                            (*curFile)->currLine, //The line of this error
                            (*curFile)->currCol + i); //The column the error occurs

                        }else if(((*curFile)->currLineCon)[i] != '.' && (!isalpha(((*curFile)->currLineCon)[i]) && !isdigit(((*curFile)->currLineCon)[i]) && ((*curFile)->currLineCon)[i] != '_')){

                            rpt(REPORT_CODE_ERROR, //This is an error
                            REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                            MSG_PPC_LINKER_USING_RESTRICTEDNAMING, //This is the custom error message (check /compiler/errors/messages.h)
                            srcPth, //The source of this error
                            (*curFile)->currLine, //The line of this error
                            (*curFile)->currCol + i); //The column the error occurs

                        }else if(lokForNum && ((*curFile)->currLineCon)[i] == '.'){

                            rpt(REPORT_CODE_ERROR, //This is an error
                            REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                            MSG_PPC_LINKER_USING_EMPTYSECTION, //This is the custom error message (check /compiler/errors/messages.h)
                            srcPth, //The source of this error
                            (*curFile)->currLine, //The line of this error
                            (*curFile)->currCol + stmIndx); //The column the error occurs

                        }else{

                            pthLen++;

                            libPth = realloc(libPth, sizeof(char)*pthLen);

                            if(((*curFile)->currLineCon)[i] == '.')
                                libPth[pthLen - 2] = PATH_SLASH_TYP_CHAR;
                            else
                                libPth[pthLen - 2] = ((*curFile)->currLineCon)[i];

                            libPth[pthLen - 1] = '\0';

                        }

                        lokForNum = 0;

                        if(((*curFile)->currLineCon)[i] == '.'){ //Look inside another folder now!

                            lokForNum = 1;

                        }

                    }

                }

                if(lokForNum){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_USING_EMPTYSECTION, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + stmIndx); //The column the error occurs

                }else if(!isFsh){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_USING_SEMICOLON, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + len); //The column the error occurs

                }else{

                    pthLen += strlen(MUR_LIB_FILEEXT);

                    char *tmpLibPth = apdStr(libPth, MUR_LIB_FILEEXT);
                    free(libPth);
                    libPth = pthAnl(COMPILER_START_DIR, tmpLibPth);

                    free(tmpLibPth);

                    FILE *libPtr = fopen(libPth, "r");

                    if(libPtr == NULL){

                        char *tmpMsg = malloc(sizeof(char)*(88 + strlen(libPth) + 1));

                        sprintf(tmpMsg, "There was an attempt to access the file <%s>, which does not exist, or cannot be accessed!", libPth);

                        writeLogLine("Preprocessor", 0, tmpMsg, 0, 0, 0);

                        free(tmpMsg);

                        rpt(REPORT_CODE_ERROR, //This is an error
                        REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                        MSG_PPC_LINKER_USING_INACCESSIBLEFILE, //This is the custom error message (check /compiler/errors/messages.h)
                        srcPth, //The source of this error
                        (*curFile)->currLine, //The line of this error
                        (*curFile)->currCol + stmIndx); //The column the error occurs

                    }else{

                        //Include this file!
                        insSubFil(libPtr, //Sub-file pointer
                                  dstFilPtr, //Tmp file pointer
                                  curFile, //Original file info
                                  libPth, //Sub-file path
                                  srcPth, //Source path
                                  stmIndx, //an added value to the column for the `rpt` function
                                  stmIndx); //an added value to the column for the final data

                    }

                }

                free(libPth);

                rmvPrcSec(curFile,
                          &len,
                          &i,
                          stmIndx);

            }else if(ENABLE_IMPORT_STATEMENT && i + 5 < len &&
                    ((*curFile)->currLineCon)[i] == 'i' &&
                    ((*curFile)->currLineCon)[i + 1] == 'm' &&
                    ((*curFile)->currLineCon)[i + 2] == 'p' &&
                    ((*curFile)->currLineCon)[i + 3] == 'o' &&
                    ((*curFile)->currLineCon)[i + 4] == 'r' &&
                    ((*curFile)->currLineCon)[i + 5] == 't' &&
                    ((i + 6 < len) ?
                        (
                            ((*curFile)->currLineCon)[i + 6] == ' ' ||
                            ((*curFile)->currLineCon)[i + 6] == '"' ||
                            ((*curFile)->currLineCon)[i + 6] == ';'
                        ) :
                        1
                    )){

                //The "import" statement has been detected!
                writeLogLine("Preprocessor", 0, "An 'import' statement has been detected!", 1, (*curFile)->currLine, (*curFile)->currCol + i);

                int stmIndx = i, lokForStr = 1, pthLen = 0, isDon = 0, fndCls = 0, fndEnd = 0, isFstNoSpc = 1;

                char *tmpStr = malloc(1*sizeof(char));

                for(i += 7; i < len; i++){

                    if(((*curFile)->currLineCon)[i] == ';'){ //Find the end of this command!

                        fndEnd = 1;
                        break;

                    }

                    if(!isspace(((*curFile)->currLineCon)[i])) {

                        if(isFstNoSpc == 1){

                            isFstNoSpc = 0;

                            if(((*curFile)->currLineCon)[i] != '"'){

                                isFstNoSpc = -1;
                                break;

                            }

                        }

                        if(isDon){

                            exit(-100); //Well, this is not supposed to happen!
                            //This may not be possible, IDK.

                        }

                        if(lokForStr && ((*curFile)->currLineCon)[i] == '"'){

                            lokForStr = 0;

                        }else if(((*curFile)->currLineCon)[i] != '"'){ //Could crash when there's no closing quote

                            tmpStr[pthLen] = ((*curFile)->currLineCon)[i];
                            tmpStr = realloc(tmpStr, (++pthLen + 1)*sizeof(char));

                        }else{ //Well, we're done here!

                            isDon = 1;

                            //Start importing this file!
                            tmpStr[pthLen] = '\0';

                            int orgImpPthLen = strlen(tmpStr); //Save the string length!

                            char *fnlPth = pthAnl(wrkstn.Path, tmpStr);

                            char *tmpMsgStr = malloc((77 + strlen(fnlPth) + 2)*sizeof(char));

                            sprintf(tmpMsgStr, "Importing the content of the file <%s> into the temporary output file.", fnlPth);

                            writeLogLine("Preprocessor", 0, tmpMsgStr, 1, (*curFile)->currLine, stmIndx + (*curFile)->currCol);

                            FILE *subTmpPtr = fopen(fnlPth, "r");

                            if(subTmpPtr == NULL){

                                char *tmpMsg = malloc(sizeof(char)*(88 + strlen(fnlPth) + 1));

                                sprintf(tmpMsg, "There was an attempt to access the file <%s>, which does not exist, or cannot be accessed!", fnlPth);

                                writeLogLine("Preprocessor", 0, tmpMsg, 0, 0, 0);

                                free(tmpMsg);

                                rpt(REPORT_CODE_ERROR, //This is an error
                                REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                                MSG_PPC_LINKER_IMPORT_INACCESSIBLEFILE, //This is the custom error message (check /compiler/errors/messages.h)
                                srcPth, //The source of this error
                                (*curFile)->currLine, //The line of this error
                                (*curFile)->currCol + i - orgImpPthLen); //The column the error occurs

                            }

                            insSubFil(subTmpPtr, //Sub-file pointer
                                      dstFilPtr, //Tmp file pointer
                                      curFile, //Original file info
                                      fnlPth, //Sub-file path
                                      srcPth, //Source path
                                      i - orgImpPthLen, //an added value to the column for the `rpt` function
                                      stmIndx); //an added value to the column for the final data

                            sprintf(tmpMsgStr, "Finished importing the content of the file <%s> into the temporary output file.", fnlPth);

                            writeLogLine("Preprocessor", 0, tmpMsgStr, 1, (*curFile)->currLine, stmIndx + (*curFile)->currCol);

                            free(tmpMsgStr);
                            free(fnlPth);

                        }

                    }

                }

                if(isFstNoSpc == -1){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_IMPORT_NOSTRINGINPUT, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + i); //The column the error occurs

                }else if(!isDon && lokForStr){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_IMPORT_NOINPUT, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + stmIndx); //The column the error occurs

                }else if(!isDon){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_IMPORT_CLOSINGQUOTE, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + i); //The column the error occurs

                }else if(!fndEnd || (!fndEnd && sizeof(tmpStr) == sizeof(char))) {

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_IMPORT_SEMICOLON, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + i); //The column the error occurs

                }

                free(tmpStr); //Free the path

                rmvPrcSec(&(*curFile),
                          &len,
                          &i,
                          stmIndx);

            }else if(ENABLE_TELL_STATEMENT && i + 5 < len &&
                    ((*curFile)->currLineCon)[i] == 't' &&
                    ((*curFile)->currLineCon)[i + 1] == 'e' &&
                    ((*curFile)->currLineCon)[i + 2] == 'l' &&
                    ((*curFile)->currLineCon)[i + 3] == 'l' &&
                    (
                        (i + 4 < len) ? (
                            ((*curFile)->currLineCon)[i + 4] == ' ' ||
                            ((*curFile)->currLineCon)[i + 4] == '"' ||
                            ((*curFile)->currLineCon)[i + 4] == ';'
                        ) :
                        1
                    )){

                //The "tell" statement has been detected!
                writeLogLine("Preprocessor", 0, "A 'tell' statement has been detected!", 1, (*curFile)->currLine, (*curFile)->currCol + i);

                int stmIndx = i, lokForStr = 1, pthLen = 0, isDon = 0, fndCls = 0, fndEnd = 0, isFstNoSpc = 1;

                char *tmpStr = malloc(1*sizeof(char));

                for(i += 5; i < len; i++){

                    if(((*curFile)->currLineCon)[i] == ';'){ //Find the end of this command!

                        fndEnd = 1;
                        break;

                    }

                    if(!isspace(((*curFile)->currLineCon)[i])) {

                        if(isFstNoSpc == 1){

                            isFstNoSpc = 0;

                            if(((*curFile)->currLineCon)[i] != '"'){

                                isFstNoSpc = -1;
                                break;

                            }

                        }

                        if(isDon){

                            exit(-100); //Well, this is not supposed to happen!
                            //This may not be possible, IDK.

                        }

                        if(lokForStr && ((*curFile)->currLineCon)[i] == '"'){

                            lokForStr = 0;

                        }else if(((*curFile)->currLineCon)[i] != '"'){ //Could crash when there's no closing quote

                            tmpStr[pthLen] = ((*curFile)->currLineCon)[i];
                            tmpStr = realloc(tmpStr, (++pthLen + 1)*sizeof(char));

                        }else{ //Well, we're done here!

                            isDon = 1;

                            //Start saving this data!
                            tmpStr[pthLen] = '\0';

                            insTllDat(tmpStr);

                            //int orgImpPthLen = strlen(tmpStr); //Save the string length!
                            //char *fnlPth = pthAnl(wrkstn.Path, tmpStr);

                            writeLogLine("Preprocessor", 0, "Saving the content of the tell method into the `.tll` output file.", 1, (*curFile)->currLine, stmIndx + (*curFile)->currCol);

                        }

                    }

                }

                if(isFstNoSpc == -1){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_TELL_NOSTRINGINPUT, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + i); //The column the error occurs

                }else if(!isDon && lokForStr){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_TELL_NOINPUT, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + stmIndx); //The column the error occurs

                }else if(!isDon){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_TELL_CLOSINGQUOTE, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + i); //The column the error occurs

                }else if(!fndEnd || (!fndEnd && sizeof(tmpStr) == sizeof(char))) {

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_TELL_SEMICOLON, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + i); //The column the error occurs

                }

                free(tmpStr); //Free the path

                rmvPrcSec(&(*curFile),
                          &len,
                          &i,
                          stmIndx);

            }else if(ENABLE_DEFINE_STATEMENT && i + 6 < len && ((*curFile)->currLineCon)[i] == 'd' && ((*curFile)->currLineCon)[i + 1] == 'e' && ((*curFile)->currLineCon)[i + 2] == 'f' && ((*curFile)->currLineCon)[i + 3] == 'i' && ((*curFile)->currLineCon)[i + 4] == 'n' && ((*curFile)->currLineCon)[i + 5] == 'e' && ((*curFile)->currLineCon)[i + 6] == ' '){

                //The "define" statement has been detected!
                writeLogLine("Preprocessor", 0, "A 'define' statement has been detected!", 1, (*curFile)->currLine, (*curFile)->currCol + i);

                int stmIndx = i, lokForNum = 1, isFsh = 0, varLen = 1, valLen = 1, skpFrsSpc = 0, fndSpc = 0, alwSpc = 0;

                char *varId = malloc(sizeof(char)*varLen),
                     *varVal = malloc(sizeof(char)*valLen);
                varId[0] = '\0';

                for(i += 7; i < len; i++){

                    if(((*curFile)->currLineCon)[i] == ';'){

                        isFsh = 1;
                        break;

                    }

                    if(skpFrsSpc && !fndSpc && isspace(((*curFile)->currLineCon)[i]))
                        fndSpc = 1;

                    if(!isspace(((*curFile)->currLineCon)[i]) || alwSpc){

                        skpFrsSpc = 1;

                        if(!fndSpc && lokForNum && isdigit(((*curFile)->currLineCon)[i])) { //Only accept names that start with letters

                            rpt(REPORT_CODE_ERROR, //This is an error
                            REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                            MSG_PPC_LINKER_DEFINE_NODIGITSATSTART, //This is the custom error message (check /compiler/errors/messages.h)
                            srcPth, //The source of this error
                            (*curFile)->currLine, //The line of this error
                            (*curFile)->currCol + i); //The column the error occurs

                        }else if(!fndSpc && !isalpha(((*curFile)->currLineCon)[i]) && !isdigit(((*curFile)->currLineCon)[i]) && ((*curFile)->currLineCon)[i] != '_'){

                            rpt(REPORT_CODE_ERROR, //This is an error
                            REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                            MSG_PPC_LINKER_DEFINE_RESTRICTEDNAMING, //This is the custom error message (check /compiler/errors/messages.h)
                            srcPth, //The source of this error
                            (*curFile)->currLine, //The line of this error
                            (*curFile)->currCol + i); //The column the error occurs

                        }else if(!fndSpc){

                            varLen++;

                            varId = realloc(varId, sizeof(char)*varLen);

                            varId[varLen - 2] = ((*curFile)->currLineCon)[i];

                            varId[varLen - 1] = '\0';

                            alwSpc = 1;

                        }else{

                            valLen++;

                            varVal = realloc(varVal, sizeof(char)*valLen);

                            varVal[valLen - 2] = ((*curFile)->currLineCon)[i];

                            varVal[valLen - 1] = '\0';
                            //varVal

                        }

                        lokForNum = 0;

                    }

                }

                if(lokForNum){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_DEFINE_MISSINGNAME, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + stmIndx); //The column the error occurs

                }else if(!fndSpc){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_DEFINE_MISSINGVALUE, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + stmIndx); //The column the error occurs

                }else if(!isFsh){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_LINKER_DEFINE_SEMICOLON, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    (*curFile)->currLine, //The line of this error
                    (*curFile)->currCol + len); //The column the error occurs

                }else{

                    char *tmpDatStr = malloc(sizeof(char)*(
                        strlen(varId) +
                        strlen(varVal) +
                        1 +
                        10 +
                        18 +
                        1
                    ));

                    sprintf(tmpDatStr, "%s %s <Zx%09X> <Zx%09X>", varId, varVal, (*curFile)->currLine, (*curFile)->currCol + i - strlen(varVal) + 1);

                    savDat(DATA_VALUE, tmpDatStr);

                    free(tmpDatStr);

                }

                free(varId);
                free(varVal);

                rmvPrcSec(&(*curFile),
                          &len,
                          &i,
                          stmIndx);

            }/*else if(ENABLE_SETSIZE_STATEMENT && i + 7 < len && ((*curFile)->currLineCon)[i] == 's' && ((*curFile)->currLineCon)[i + 1] == 'e' && ((*curFile)->currLineCon)[i + 2] == 't' && ((*curFile)->currLineCon)[i + 3] == 's' && ((*curFile)->currLineCon)[i + 4] == 'i' && ((*curFile)->currLineCon)[i + 5] == 'z' && ((*curFile)->currLineCon)[i + 6] == 'e' && ((*curFile)->currLineCon)[i + 7] == ' '){

                //The "setsize" statement has been detected!
                writeLogLine("Preprocessor", 0, "A 'setsize' statement has been detected!", 1, (*curFile)->currLine, (*curFile)->currCol + i);

            }*/

        }

    }

}

void chkForCnst(FileInfo **curFile){

    //Remember, constants can be anywhere
    //outside quotes!

    //int hitSpc = 0, prvSpc = 0;

    for(int i = 0; i < strlen((*curFile)->currLineCon); i++){

        //This code won't do...

        //char *val = getDatByNam(DATA_VALUE, tmpStr, 1);

        /*if(hitSpc > 0 && !isspace(((*curFile)->currLineCon)[i])){

            char *tmpStr = getStrPrt((*curFile)->currLineCon, prvSpc, hitSpc, 0),
                 *val = getDatByNam(DATA_VALUE, tmpStr, 1);

            //printf("\n[%s]", val);

            if(val[0] != '\0'){

                printf("\n%s", val);

                int lenShf = strlen(val) - strlen(tmpStr);

                char *tmpFstPrtStr = getStrPrt((*curFile)->currLineCon, 0, prvSpc + 1, 0),
                     *tmpScdPrtStr = getStrPrt((*curFile)->currLineCon, hitSpc, strlen((*curFile)->currLineCon), 0);

                sprintf((*curFile)->currLineCon, "%s%s%s", tmpFstPrtStr, val, tmpScdPrtStr);

                free(tmpFstPrtStr);
                free(tmpScdPrtStr);

                i += lenShf;

            }

            free(tmpStr);
            free(val);

            hitSpc = -hitSpc;

        }

        if(hitSpc <= 0 && isspace(((*curFile)->currLineCon)[i])){

            prvSpc = -hitSpc;
            hitSpc = i;

        }*/

    }

}