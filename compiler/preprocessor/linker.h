#include "path_analyser.h"

FileInfo* chkForPprFunc(FileInfo *curFile, FILE *dstFilPtr, char *srcPth){

    int len = strlen(curFile->currLineCon), inStr = 0, inChr = 0;

    for(int i = 0; i < len; i++){

        //(curFile->currLineCon)[i]; //Current character

        if((i - 1 != -1) ? ((curFile->currLineCon)[i - 1] != '\\') : 1) { //Look for the '\' char

            if(!inChr && (curFile->currLineCon)[i] == '"') //String opening/closing
                inStr = !inStr;

            if(!inStr && (curFile->currLineCon)[i] == '\'') //Char opening/closing
                inChr = !inChr;

        }

        int shdChk = !inStr && !inChr;

        if(shdChk && (curFile->currLineCon)[i] == '{'){ //Beaware, a new zone opening has been detected!

            curFile->curZon++;

        }else if(shdChk && (curFile->currLineCon)[i] == '}'){  //Beaware, a new zone closing has been detected!

            curFile->curZon--;

        }else if(shdChk && curFile->curZon == 0 && (i == 0 || isspace((curFile->currLineCon)[i - 1]) || (curFile->currLineCon)[i - 1] == ';')){

            //You can start looking now!

            if(ENVI_ENABLE_SEPARATE_METHOD){

                //

            }

            if(ENABLE_USING_STATEMENT && i + 5 < len && (curFile->currLineCon)[i] == 'u' && (curFile->currLineCon)[i + 1] == 's' && (curFile->currLineCon)[i + 2] == 'i' && (curFile->currLineCon)[i + 3] == 'n' && (curFile->currLineCon)[i + 4] == 'g' && (curFile->currLineCon)[i + 5] == ' '){

                //The "using" statement has been detected!
                writeLogLine("Preprocessor", 0, "A 'using' statement has been detected!", 1, curFile->currLine, curFile->currCol + i);

                int stmIndx = i, lokForNum = 1;

                //fprintf(dstFilPtr, "[{%s},%d;%d]-%s\n", srcPth, curFile->currLine, curFile->currCol, curFile->currLineCon);

                for(i += 6; i < len; i++){

                    if((curFile->currLineCon)[i] == ';')
                        break;

                    if(!isspace((curFile->currLineCon)[i])) {

                        if(lokForNum && isdigit((curFile->currLineCon)[i])) {

                            //Oops, that's not allowed!
                            exit(-1);

                        }else
                            lokForNum = 0;

                        if((curFile->currLineCon)[i] == '.'){ //Look inside another folder now!

                            lokForNum = 1;

                        }

                    }
                    
                    //Use "break" once you reach a ";"

                }

            }

            if(ENABLE_IMPORT_STATEMENT && i + 6 < len && (curFile->currLineCon)[i] == 'i' && (curFile->currLineCon)[i + 1] == 'm' && (curFile->currLineCon)[i + 2] == 'p' && (curFile->currLineCon)[i + 3] == 'o' && (curFile->currLineCon)[i + 4] == 'r' && (curFile->currLineCon)[i + 5] == 't' && ((curFile->currLineCon)[i + 6] == ' ' || (curFile->currLineCon)[i + 6] == '"')){

                //The "import" statement has been detected!
                writeLogLine("Preprocessor", 0, "An 'import' statement has been detected!", 1, curFile->currLine, curFile->currCol + i);

                int stmIndx = i, lokForStr = 1, pthLen = 0, isDon = 0, fndEnd = 0;

                char *tmpStr = malloc(1*sizeof(char));

                for(i += 7; i < len; i++){

                    if((curFile->currLineCon)[i] == ';'){ //Find the end of this command!

                        fndEnd = 1;
                        break;

                    }

                    if(!isspace((curFile->currLineCon)[i])) {

                        if(isDon){

                            exit(-1); //Well, this is not supposed to happen!

                        }

                        if(lokForStr && (curFile->currLineCon)[i] == '"'){

                            lokForStr = 0;

                        }else if((curFile->currLineCon)[i] != '"'){

                            tmpStr[pthLen] = (curFile->currLineCon)[i];
                            tmpStr = realloc(tmpStr, (++pthLen + 1)*sizeof(char));

                        }else{ //Well, we're done here!

                            isDon = 1;

                            //Start importing this file!
                            tmpStr[pthLen] = '\0';

                            char *fnlPth = pthAnl(wrkstn.Path, tmpStr);

                            char *tmpMsgStr = malloc((77 + strlen(fnlPth) + 2)*sizeof(char));

                            sprintf(tmpMsgStr, "Importing the content of the file <%s> into the temporary output file.", fnlPth);

                            writeLogLine("Preprocessor", 0, tmpMsgStr, 1, curFile->currLine, stmIndx);

                            //

                            //sprintf("<%s>@%s", tmpStr, srcPth);
                            //fnlPth;
                            //
                            FILE *subTmpPtr = fopen(fnlPth, "r");

                            if(subTmpPtr == NULL){

                                char *tmpMsg = malloc(sizeof(char)*(88 + strlen(fnlPth) + 1));

                                sprintf(tmpMsg, "There was an attempt to access the file <%s>, which does not exist, or cannot be accessed!", fnlPth);

                                writeLogLine("Preprocessor", 0, tmpMsg, 0, 0, 0);

                                free(tmpMsg);

                                exit(-1);

                            }

                            //

                            FileInfo *subFilInf = checkFlags(subTmpPtr, fnlPth, 0); //An object that contains the sub-file info!

                            //fprintf(dstFilPtr, "[{curFil@%s},%d;%d]->%s\n", srcPth, subFilInf->currLine, subFilInf->currCol, subFilInf->currLineCon);

                            printf("\n[Debug] [Sub] Mode: %c\n", subFilInf->mode);
                            printf("[Debug] [Sub] Is Full: %d\n", subFilInf->isFull);
                            printf("[Debug] [Sub] Current Line Content: %s\n", subFilInf->currLineCon);
                            printf("[Debug] [Sub] Current Line Original Content: %s\n", subFilInf->currOLineCon);
                            printf("[Debug] [Sub] Path: %s\n", subFilInf->path);

                            if(subFilInf->mode == 'U'){ //This is neither a `.mur` file nor a `.lib.mur` file

                                writeLogLine("Compiler Manager", 2, "Unknown input file extension!", 0, 0, 0);

                                exit(-1); //Exit! Don't worry about the allocated memory, the system is gonna clean it up.

                            }else{

                                char *tmpSrcStr = malloc(sizeof(char)*(strlen(srcPth) + strlen(fnlPth) + 4));

                                int pthDatId = savDat(DATA_PATH, fnlPth);

                                sprintf(tmpSrcStr, "%06X@%s", pthDatId, srcPth);

                                ppcRead(subFilInf, dstFilPtr, tmpSrcStr); //Let the preprocessor do its thing, again!

                                free(tmpSrcStr);

                            }

                            fclose(subTmpPtr);
                            //freeFileDatObj(subFilInf);

                            sprintf(tmpMsgStr, "Finished importing the content of the file <%s> into the temporary output file.", fnlPth);

                            writeLogLine("Preprocessor", 0, tmpMsgStr, 1, curFile->currLine, stmIndx);

                            free(tmpMsgStr);
                            free(fnlPth);

                        }

                    }
                    
                    //Use "break" once you reach a ";"

                }

                if(!fndEnd || (!fndEnd && sizeof(tmpStr) == sizeof(char))) {

                    exit(-1); //THis is not supposed to happen!

                }

                free(tmpStr); //Free the path


            }

            if(ENABLE_DEFINE_STATEMENT && i + 6 < len && (curFile->currLineCon)[i] == 'd' && (curFile->currLineCon)[i + 1] == 'e' && (curFile->currLineCon)[i + 2] == 'f' && (curFile->currLineCon)[i + 3] == 'i' && (curFile->currLineCon)[i + 4] == 'n' && (curFile->currLineCon)[i + 5] == 'e' && (curFile->currLineCon)[i + 6] == ' '){

                //The "define" statement has been detected!
                writeLogLine("Preprocessor", 0, "A 'define' statement has been detected!", 1, curFile->currLine, curFile->currCol + i);

            }

            if(ENABLE_SETSIZE_STATEMENT && i + 7 < len && (curFile->currLineCon)[i] == 's' && (curFile->currLineCon)[i + 1] == 'e' && (curFile->currLineCon)[i + 2] == 't' && (curFile->currLineCon)[i + 3] == 's' && (curFile->currLineCon)[i + 4] == 'i' && (curFile->currLineCon)[i + 5] == 'z' && (curFile->currLineCon)[i + 6] == 'e' && (curFile->currLineCon)[i + 7] == ' '){

                //The "setsize" statement has been detected!
                writeLogLine("Preprocessor", 0, "A 'setsize' statement has been detected!", 1, curFile->currLine, curFile->currCol + i);

            }

        }

    }

    /*FileInfo *subFilInf = checkFlags(filePtr, full_path, 0); //An object that contains the sub-file info!

    fprintf(dstFilPtr, "[{curFil@%s},%d;%d]->%s\n", srcPth, subFilInf->currLine, subFilInf->currCol, subFilInf->currLineCon);

    writeLogLine("Preprocessor", 0, "Inserted the filtered code into the temporary output file.", 0, 0, 0);*/

    return curFile;

}