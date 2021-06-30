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

    fileInf->mode;
    fileInf->isFull;
    fileInf->currLineCon;
    fileInf->currOLineCon;
    fileInf->path;
    fileInf->filePtr;
    fileInf->fileStrPtr;
    fileInf->currLine;
    fileInf->currCol;
    fileInf->nextCol;

    int keepLoop = 1, wait = 1;

    while(keepLoop){

        writeLogLine("Preprocessor", 0, "New processing loop started.", 1, fileInf->currLine, fileInf->currCol);

        if(ENABLE_COMMENTS && ENVI_ENABLE_COMMENTS && !isStrEmpty(fileInf->currLineCon))
            fileInf = chkForCom(fileInf); //Remove the comments

        if(ENABLE_PREPROCESSOR_METHODS && ENVI_ENABLE_COMMENTS && !isStrEmpty(fileInf->currLineCon) && !waitForComm){

            writeLogLine("Preprocessor", 0, "Checking for preprocessor methods...", 1, fileInf->currLine, fileInf->currCol);
            fileInf = chkForPprFunc(fileInf); //Check for the preprocessor functions

        }

        if(!isStrEmpty(fileInf->currLineCon) && !waitForComm){

            //if((fileInf->currLineCon)[strlen(fileInf->currLineCon) - 1] == '\n')
            //    (fileInf->currLineCon)[strlen(fileInf->currLineCon) - 1] = '\0';

            //fprintf(desFilePtr, "@[%d,%d]%s\n", fileInf->currLine, fileInf->currCol, fileInf->currLineCon);
            fprintf(desFilePtr, "@[%d,%d]%s", fileInf->currLine, fileInf->currCol, fileInf->currLineCon);

            writeLogLine("Preprocessor", 0, "Inserted the filtered code into the temporary output file.", 0, 0, 0);

        }

        printf("\n[Debug]nextCol: %d, currCol: %d, OLen: %d, Line: %d\n", fileInf->nextCol, fileInf->currCol, strlen(fileInf->currOLineCon), fileInf->currLine);

        if(keepLoop && (fileInf->nextCol == fileInf->currCol || fileInf->nextCol >= strlen(fileInf->currOLineCon) + 1)){ //Get next line only if the column is still set to 1 or if it's set to the last column in the current line

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

                strcpy(fileInf->currLineCon, fileInf->currOLineCon);

                fileInf->currLine++;

                fileInf->currCol = 1;
                fileInf->nextCol = 1;

            }

        }else{

            writeLogLine("Preprocessor", 0, "Getting the current line content starting from the specified column...", 0, 0, 0);

            //Move the column content!
            fileInf->currLineCon = getStrPrt(fileInf->currOLineCon, fileInf->nextCol - 1, strlen(fileInf->currOLineCon) - 1, 0);

            fileInf->currCol = fileInf->nextCol;

        }

    }

}