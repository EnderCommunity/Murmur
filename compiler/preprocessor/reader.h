void ppcRead(FileInfo *fileInf, FILE *desFilPtr, char *filPth);

#include "data.h"
#include "tell.h"
#include "linker.h"

FileInfo* chngFileCol(FileInfo *tmp, int col){

    tmp->currCol = col;

    tmp->currLineCon = getStrPrt(tmp->currLineCon, tmp->currCol - 1, strlen(tmp->currLineCon), 0);

    return tmp;

}

int waitForComm = 0;

#include "comments.h"

void ppcRead(FileInfo *fileInf, FILE *desFilPtr, char *filPth){

    int keepLoop = !feof(fileInf->filePtr), wait = 1;

    if(!keepLoop){

        keepLoop = 1;
        wait = 0;
        writeLogLine("Preprocessor", 0, "Last line detected!", 0, 0, 0);

    }

    int linOrgLen = strlen(fileInf->currOLineCon),
        linFstChrCnd = fileInf->currOLineCon[0] != '\r';

    while(keepLoop){

        if(linOrgLen != 0 && linFstChrCnd){

            writeLogLine("Preprocessor", 0, "New processing loop started.", 1, fileInf->currLine, fileInf->currCol);
            writeLogLine("Preprocessor", 1, fileInf->currLineCon, 0, 0, 0);
 
            if(ENABLE_COMMENTS && ENVI_ENABLE_COMMENTS && !isStrEmpty(fileInf->currLineCon))
                chkForCom(&fileInf); //Remove the comments

            if(REMOVE_WHITESPACE_AT_LINE_END && !waitForComm && !isStrEmpty(fileInf->currLineCon)){

                while(strlen(fileInf->currOLineCon) != 1 && isspace(fileInf->currLineCon[strlen(fileInf->currLineCon) - 1])){ //Remove the extra whitespace

                    //Shif by one char
                    fileInf->currLineCon[strlen(fileInf->currLineCon) - 1] = '\0';

                }

            }

            if(ENABLE_PREPROCESSOR_METHODS && ENVI_CHECK_FOR_PREPROCESSOR_METHODS && !waitForComm && !isStrEmpty(fileInf->currLineCon)){

                writeLogLine("Preprocessor", 0, "Checking for preprocessor methods...", 1, fileInf->currLine, fileInf->currCol);
                chkForPprFunc(&fileInf, desFilPtr, filPth); //Check for the preprocessor functions

            }

            if(ENABLE_PREPROCESSOR_METHODS && ENVI_CHECK_FOR_PREPROCESSOR_METHODS && !waitForComm && !isStrEmpty(fileInf->currLineCon)){

                writeLogLine("Preprocessor", 0, "Checking for constants...", 1, fileInf->currLine, fileInf->currCol);
                chkForCnst(&fileInf); //Replace the defined constants

            }

            if(!waitForComm && !isStrEmpty(fileInf->currLineCon)){

                fprintf(desFilPtr, "[{%s%s},%d;%d]->%s\n", ((fileInf->isSptZon) ? fileInf->curZonId : ""), filPth, fileInf->currLine, fileInf->currCol, fileInf->currLineCon);

                writeLogLine("Preprocessor", 0, "Inserted the filtered code into the temporary output file.", 0, 0, 0);

            }

        }

        if(keepLoop && (fileInf->nextCol == fileInf->currCol || fileInf->nextCol - linOrgLen >= 0 - END_OF_LINE_COUNT)){ //Get next line only if the column is still set to 1 or if it's set to the last column in the current line
                                                                                                                  //^ this value has been changed from "1" to "0"

            writeLogLine("Preprocessor", 0, "Getting the content of the next line...", 0, 0, 0);

            fgets(fileInf->currOLineCon, MAX_LINE_LENGTH, fileInf->filePtr); //Move to the next line!

            if(wait)
                keepLoop = !feof(fileInf->filePtr);

            if(!wait)
                keepLoop = 0;

            if(!keepLoop && wait){

                keepLoop = 1;
                wait = 0;
                writeLogLine("Preprocessor", 0, "Last line detected!", 0, 0, 0);

            }

            if(keepLoop){

                fileInf->currLine++;

                fileInf->currCol = 1;
                fileInf->nextCol = 1;

                if(fileInf->currOLineCon[strlen(fileInf->currOLineCon) - 1] == '\n')
                    fileInf->currOLineCon[strlen(fileInf->currOLineCon) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

                if(REMOVE_WHITESPACE_AT_LINE_START)
                    while(strlen(fileInf->currOLineCon) != 1 && isspace(fileInf->currOLineCon[0])){ //Remove the extra whitespace without losing track of the column number

                        //Shif by one char
                        fileInf->currOLineCon = shfStr(fileInf->currOLineCon, 1);

                        fileInf->currCol++;

                    }

                linOrgLen = strlen(fileInf->currOLineCon);
                linFstChrCnd = fileInf->currOLineCon[0] != '\r';

                fileInf->nextCol = fileInf->currCol;


                strcpy(fileInf->currLineCon, fileInf->currOLineCon);

                writeLogLine("Preprocessor", 0, "The line variable content changed successfully!", 0, 0, 0);

            }else{

                if(waitForComm){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_READER_MLCOMMENTEND, //This is the custom error message (check /compiler/errors/messages.h)
                    filPth, //The source of this error
                    fileInf->currLine, //The line of this error
                    fileInf->currCol); //The column the error occurs

                }

                if(fileInf->isSptZon){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_READER_SPRZONEEND, //This is the custom error message (check /compiler/errors/messages.h)
                    filPth, //The source of this error
                    fileInf->currLine, //The line of this error
                    fileInf->currCol); //The column the error occurs

                }

            }

        }else{

            writeLogLine("Preprocessor", 0, "Getting the current line content starting from the specified column...", 0, 0, 0);

            //Shift the line content!

            char *tmpStr = getStrPrt(fileInf->currOLineCon, fileInf->nextCol - 1 - fileInf->currCol + 1, strlen(fileInf->currOLineCon), 0);

            strcpy(fileInf->currLineCon, tmpStr);
            strcpy(fileInf->currOLineCon, fileInf->currLineCon);

            free(tmpStr);

            fileInf->currCol = fileInf->nextCol;

        }

    }

    if(fileInf->isFull)
        fprintf(desFilPtr, "[FileEnd]");

    freeFileDatObj(fileInf);

}