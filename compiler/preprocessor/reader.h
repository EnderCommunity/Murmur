#include "linker.h"
#include "import.h"

FileInfo* chngFileCol(FileInfo *tmp, int col){

    tmp->currCol = col;

    tmp->currLineCon = getStrPrt(tmp->currLineCon, tmp->currCol - 1, strlen(tmp->currLineCon), 0);

    return tmp;

}

int waitForComm = 0;

#include "comments.h"

void ppcRead(FileInfo *fileInf, FILE *desFilePtr){

    /*fileInf->mode;
    fileInf->isFull;
    fileInf->currLineCon;
    fileInf->currOLineCon;
    fileInf->path;
    fileInf->filePtr;
    fileInf->fileStrPtr;
    fileInf->currLine;
    fileInf->currCol;
    fileInf->nextCol;*/

    int keepLoop = 1, wait = 1;

    while(keepLoop){

        writeLogLine("Preprocessor", 0, "New processing loop started.", 1, fileInf->currLine, fileInf->currCol);

        /*char *tmpStr;
        tmpStr = apdStr("The current loop line content is -> \"", apdStr(fileInf->currLineCon, "\""));
        writeLogLine("Preprocessor", 1, tmpStr, 0, 0, 0);*/
        writeLogLine("Preprocessor", 1, fileInf->currLineCon, 0, 0, 0);
 
        if(ENABLE_COMMENTS && ENVI_ENABLE_COMMENTS && !isStrEmpty(fileInf->currLineCon))
            fileInf = chkForCom(fileInf); //Remove the comments

        if(ENABLE_PREPROCESSOR_METHODS && ENVI_CHECK_FOR_PREPROCESSOR_METHODS && !isStrEmpty(fileInf->currLineCon) && !waitForComm){

            writeLogLine("Preprocessor", 0, "Checking for preprocessor methods...", 1, fileInf->currLine, fileInf->currCol);
            fileInf = chkForPprFunc(fileInf); //Check for the preprocessor functions

        }

        if(!isStrEmpty(fileInf->currLineCon) && !waitForComm){

            fprintf(desFilePtr, "[{main},%d;%d]->%s\n", fileInf->currLine, fileInf->currCol, fileInf->currLineCon);

            writeLogLine("Preprocessor", 0, "Inserted the filtered code into the temporary output file.", 0, 0, 0);

        }

        //printf("\n[Debug]nextCol: %d, currCol: %d, OLen: %d, Line: %d\n", fileInf->nextCol, fileInf->currCol, strlen(fileInf->currOLineCon), fileInf->currLine);

        if(keepLoop && (fileInf->nextCol == fileInf->currCol || fileInf->nextCol >= strlen(fileInf->currOLineCon) + 0)){ //Get next line only if the column is still set to 1 or if it's set to the last column in the current line
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

            //keepLoop = !feof(fileInf->filePtr);

            if(keepLoop){

                fileInf->currLine++;

                fileInf->currCol = 1;
                fileInf->nextCol = 1;

                if(fileInf->currOLineCon[strlen(fileInf->currOLineCon) - 1] == '\n')
                    fileInf->currOLineCon[strlen(fileInf->currOLineCon) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

                while(isspace(fileInf->currOLineCon[0])){ //Remove the extra whitespace without losing track of the column number

                    //Shif by one char
                    fileInf->currOLineCon = shfStr(fileInf->currOLineCon, 1);

                    fileInf->currCol++;

                }

                fileInf->nextCol = fileInf->currCol;


                strcpy(fileInf->currLineCon, fileInf->currOLineCon);

                writeLogLine("Preprocessor", 0, "The line variable content changed successfully!", 0, 0, 0);

            }

        }else{

            writeLogLine("Preprocessor", 0, "Getting the current line content starting from the specified column...", 0, 0, 0);

            //Move the column content!
            /*char *tmp1 = malloc(sizeof(char)*10); itoa(fileInf->nextCol - 1, tmp1, 10);
            char *tmp2 = malloc(sizeof(char)*10); itoa(strlen(fileInf->currOLineCon) - 0, tmp2, 10);
            writeLogLine("DEBUG", 1, fileInf->currOLineCon, 0, 0, 0);
            writeLogLine("DEBUG", 1, fileInf->currLineCon, 0, 0, 0);
            writeLogLine("DEBUG", 1, tmp1, 0, 0, 0);
            writeLogLine("DEBUG", 1, tmp2, 0, 0, 0);*/

            fileInf->currLineCon = getStrPrt(fileInf->currOLineCon, fileInf->nextCol - 1, strlen(fileInf->currOLineCon) - 0, 0);
            strcpy(fileInf->currOLineCon, fileInf->currLineCon);

            /*writeLogLine("DEBUG2", 1, fileInf->currOLineCon, 0, 0, 0);
            writeLogLine("DEBUG2", 1, fileInf->currLineCon, 0, 0, 0);*/

            fileInf->currCol = fileInf->nextCol;

        }

    }

    fprintf(desFilePtr, "[FileEnd]\0");

}