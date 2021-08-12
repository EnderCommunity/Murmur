#include "import.h"

FileInfo* chkForPprFunc(FileInfo *curFile, FILE *dstFilPtr, char *srcPth){

    int len = strlen(curFile->currLineCon) - END_OF_LINE_COUNT, inStr = 0, inChr = 0;

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