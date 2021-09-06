#include "../libraries/regex/reg.h"
#include "chk.h"

//1000 `value` 0 0 0 0 | 0 0 0 0 <...> 0x000000000 1x000000000

void lexChkLop(char **curSrcPth, FILE **lexFil, char **curLin, int lopLen, int lin, int col, int newLin, int isSub){

    //printf("\n[`%s`, `%s`, `%d`, `%d`, `%d`, `%d`]", *curSrcPth, *curLin, lopLen, lin, col, newLin);

    if(2 < strlen((*curSrcPth)) && (*curSrcPth)[0] == '<' && (*curSrcPth)[1] == 'B' && (*curSrcPth)[2] == 'x'){ //This is a separate zone line!

        fprintf((*lexFil), "%d `%s` 0 0 0 0 | 0 0 0 0 [%s] 0x%09X 1x%09X\n", LEXER_ZONE_LINE, (*curLin), (*curSrcPth), lin, col);

    }else
        for(int i = 0; i < lopLen; i++, col++){ //Use this loop to scan every character one by one!

            char *currCharStr = malloc(sizeof(char)*2);
            currCharStr[0] = (*curLin)[i];
            currCharStr[1] = '\0';
            int whtSpcBef = (i != 0) ? (isspace((*curLin)[i - 1]) != 0) : 0;

            if(isspace((*curLin)[i])) { //Whitespace!

                //Do nothing!

            } else if(i + 2 < lopLen && (*curLin)[i] == '0' && ((*curLin)[i + 1] == 'x' || (*curLin)[i + 1] == 'X') && regChk("[0-9A-Fa-f]", &(*curLin)[i + 2])) { //Hex

                fprintf((*lexFil), "%d `%c", LEXER_HEX, (*curLin)[i + 2]);

                int delt = 3;

                while((delt + i < strlen((*curLin))) && regChk("[0-9A-Fa-f]", &((*curLin)[i + delt]))){

                    fprintf((*lexFil), "%c", (*curLin)[i + delt]);

                    delt++;

                }

                delt--;

                i += delt;

                fprintf((*lexFil), "` %d %d %d 0 | 0 0 0 0 [%s] 0x%09X 1x%09X\n", newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), (*curSrcPth), lin, col);

                col += delt;

            }else if(regChk("[.0-9]", currCharStr)) { //Number

                int alowDot = 1;

                if((*curLin)[i] == '.' && !isdigit((*curLin)[i + 1])){

                    //false alarm
                    fprintf((*lexFil), "%d `%c` %d %d %d 0 | %d 0 0 0 [%s] 0x%09X 1x%09X\n", LEXER_OPERATOR, (*curLin)[i], newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), !alowDot, (*curSrcPth), lin, col); //This is an operator!

                }else{

                    if((*curLin)[i] == '.')
                        alowDot = 0;

                    fprintf((*lexFil), "%d `%c", LEXER_NUMBER, (*curLin)[i]);

                    int delt = 1;

                    while(delt + i < strlen((*curLin)) && ((isdigit((*curLin)[i + delt]) || ((alowDot) ? (*curLin)[i + delt] == '.' : 0)))){

                        fprintf((*lexFil), "%c", (*curLin)[i + delt]);

                        if((*curLin)[i + delt] == '.')
                            alowDot = 0;

                        delt++;

                    }

                    delt--;

                    i += delt;

                    fprintf((*lexFil), "` %d %d %d 0 | %d 0 0 0 [%s] 0x%09X 1x%09X\n", newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), !alowDot, (*curSrcPth), lin, col);
                    //                    ^ if this value is set to '0', then this number is an integer
                    //                      if it's set to '1', then this number is of the type double/float

                    col += delt;

                }

            } else if((*curLin)[i] == '"') { //String!

                int delt = 1;

                fprintf((*lexFil), "%d `", LEXER_STRING);

                while(i + delt < strlen((*curLin)) && ((*curLin)[i + delt] != '"' || (*curLin)[i + delt - 1] == '\\')){

                    fprintf((*lexFil), "%c", (*curLin)[i + delt]);

                    delt++;

                }

                col++;
                i += delt;

                fprintf((*lexFil), "` %d %d %d 0 | 0 0 0 0 [%s] 0x%09X 1x%09X\n", newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), (*curSrcPth), lin, col);

                col += delt - 1;

            } else if((*curLin)[i] == '\'') { //Character!

                int delt = 1;

                fprintf((*lexFil), "%d `", LEXER_CHAR);

                while(i + delt < strlen((*curLin)) && ((*curLin)[i + delt] != '\'' || (*curLin)[i + delt - 1] == '\\')){

                    fprintf((*lexFil), "%c", (*curLin)[i + delt]);

                    delt++;

                }

                col++;
                i += delt;

                fprintf((*lexFil), "` %d %d %d 0 | %d 0 0 0 [%s] 0x%09X 1x%09X\n", newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), (delt == 1) ? 0 : ((delt == 2) ? 1 : ((delt == 3 && (*curLin)[i - 2] == '\\') ? 2 : 3)), (*curSrcPth), lin, col);

                col += delt - 1;

            } else if(((*curLin)[i] == 'f' && (*curLin)[i + 1] == 'a' && (*curLin)[i + 2] == 'l' && (*curLin)[i + 3] == 's' && (*curLin)[i + 4] == 'e' && !isThrMor((*curLin)[i + 5])) || ((*curLin)[i] == 't' && (*curLin)[i + 1] == 'r' && (*curLin)[i + 2] == 'u' && (*curLin)[i + 3] == 'e' && !isThrMor((*curLin)[i + 4]))){ //Boolean

                fprintf((*lexFil), "%d `%s` %d %d %d 0 | 0 0 0 0 [%s] 0x%09X 1x%09X\n", LEXER_BOOLEAN, ((*curLin)[i] == 'f') ? "false" : "true", newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), (*curSrcPth), lin, col); //This is an operator!

                if((*curLin)[i] == 'f'){

                    i += 4;

                    col += 4;

                }else{

                    i += 3;

                    col += 3;

                }

            } else if(isSyb((*curLin)[i])) { //Symbol

                char *tmpStr = malloc(sizeof(char)*(
                    1 +
                    1
                ));

                tmpStr[0] = (*curLin)[i];
                tmpStr[1] = '\0';
                int tmpStrLen = 1;

                //fprintf((*lexFil), "%d `%c", LEXER_SYMBOL, (*curLin)[i]);

                int delt = 1;

                while(i + delt < strlen((*curLin)) && isSybE((*curLin)[i + delt])){

                    //fprintf((*lexFil), "%c", (*curLin)[i + delt]);
                    tmpStr = realloc(tmpStr, sizeof(char)*(
                        (++tmpStrLen) +
                        1
                    ));
                    tmpStr[tmpStrLen - 1] = (*curLin)[i + delt];
                    tmpStr[tmpStrLen] = '\0';

                    delt++;

                }

                delt--;

                i += delt;

                char *tmpDatStr = malloc(sizeof(char)*(
                    strlen(tmpStr) +
                    1
                ));
                strcpy(tmpDatStr, tmpStr);

                int valId = getDatByNam(DATA_VALUE, tmpDatStr, 1);

                free(tmpDatStr);

                if(valId != -1){

                    char *tmpLinStr = shfStrSaf((*curLin), i - strlen(tmpStr)),
                         *tmpSrcPthStr = malloc(sizeof(char)*(
                            strlen((*curSrcPth)) +
                            11 + //<Cx000000>@
                            1
                        ));

                    sprintf(tmpSrcPthStr, "<%cx%06X>@%s", DATA_VALUE, valId, (*curSrcPth));

                    char *val = getDat(DATA_VALUE, valId, 1),
                         *fnlVal = getStrPrt(val, getStrIndx(val, "`") + 1, getLstStrIndx(val, "`"), 0);

                    //printf("\n-%s-", tmpSrcPthStr);
                    //printf("\n-%s-", val);
                    //printf("\n-%s-", fnlVal);

                    //int tmpLin = 1, tmpCol = 1;

                    // Value found!
                    lexChkLop(&tmpSrcPthStr, lexFil, &fnlVal, strlen(fnlVal), lin, col, newLin, 1);
                    //^ This is causing a crash!!! ^

                    free(fnlVal);
                    free(val);
                    free(tmpLinStr);
                    free(tmpSrcPthStr);

                }else{

                    fprintf((*lexFil), "%d `%s", LEXER_SYMBOL, tmpStr);

                    fprintf((*lexFil), "` %d %d %d 0 | 0 0 0 0 [%s] 0x%09X 1x%09X\n", newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), (*curSrcPth), lin, col);

                }

                //lexChkLop(curSrcPth, lexFil, curLin, lopLen, lin, col, newLin);


                // Change this loop to be recursive
                // 'tmpStr' is gonna be used to identify constants
                // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
                // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
                // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
                // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^

                col += delt;

                free(tmpStr);

            } else if(isCharSpcl((*curLin)[i])) { //Operator!

                fprintf((*lexFil), "%d `%c` %d %d %d 0 | 0 0 0 0 [%s] 0x%09X 1x%09X\n", LEXER_OPERATOR, (*curLin)[i], newLin, whtSpcBef, (isspace((*curLin)[i + 1]) != 0), (*curSrcPth), lin, col);

            } else {

                rpt(REPORT_CODE_ERROR, //This is an error
                REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                MSG_LXR_LEX_UNKNOWNCHAR, //This is the custom error message (check /compiler/errors/messages.h)
                (*curSrcPth), //The source of this error
                lin, //The line of this error
                col); //The column the error occurs

            }

            free(currCharStr);

            if(newLin)
                newLin = 0;

        }

}

FILE* lexProc(TmpFileStruc cFileObj){

    char *tmpLexPthStr = apdStr(cFileObj.pth, OUTPUT_LEXER_FILE_EXTENSION);

    FILE *lexFil = fopen(tmpLexPthStr, "w"); //Create a new lexer file in "write mode"

    char *tmpStr = malloc(sizeof(char)*MAX_LINE_LENGTH), *curLin = NULL;

    fgets(tmpStr, MAX_LINE_LENGTH, cFileObj.ptr); //Get the first line
    if(tmpStr[strlen(tmpStr) - 1] == '\n')
        tmpStr[strlen(tmpStr) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

    {
    
        int tmpIndx = strlen(tmpStr) - 2;
        tmpIndx = (tmpIndx != -1) ? tmpIndx : 0;

        if(tmpStr[tmpIndx] == '\r') //Hmm, maybe don't do that...
            tmpStr[tmpIndx] = '\0';

    }

    while(getStrIndx(tmpStr, "[FileEnd]") != 0){

        curLin = getStrPrt(tmpStr, getStrIndx(tmpStr, "]") + 3, strlen(tmpStr), 0); //Get the current line content

        char *curSrcPth = getStrPrt(tmpStr, 2, getStrIndx(tmpStr, "}"), 0);

        char *tmpColStr = getStrPrt(tmpStr, getStrIndx(tmpStr, ";") + 1, getStrIndx(tmpStr, "]"), 0), *tmpLinStr = getStrPrt(tmpStr, getStrIndx(tmpStr, ",") + 1, getStrIndx(tmpStr, ";"), 0);

        int col = atoi(tmpColStr), lin = atoi(tmpLinStr);

        free(tmpColStr);
        free(tmpLinStr);

        int newLin = 1, lopLen = strlen(curLin);

        lexChkLop(&curSrcPth, &lexFil, &curLin, lopLen, lin, col, newLin, 0);

        //Get the next line!
        fgets(tmpStr, MAX_LINE_LENGTH, cFileObj.ptr);

        if(tmpStr[strlen(tmpStr) - 1] == '\n')
            tmpStr[strlen(tmpStr) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

        free(curSrcPth);
        free(curLin);

    }

    fclose(lexFil); //Close the lexer file stream

    lexFil = fopen(tmpLexPthStr, "r"); //Open a new lexer stream in "read mode"

    free(tmpStr);
    free(tmpLexPthStr);

    return lexFil;

}