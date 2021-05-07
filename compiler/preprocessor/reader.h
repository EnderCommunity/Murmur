#include "linker.h"
#include "import.h"

FileInfo* chngFileCol(FileInfo *tmp, int col){

    tmp->currCol = col;

    tmp->currLineCon = getStrPrt(tmp->currLineCon, tmp->currCol - 1, strlen(tmp->currLineCon), 0);

    return tmp;

}

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

    do {

        fileInf = chkForCom(fileInf); //Remove the comments

        fileInf = chkForPprFunc(fileInf); //Check for the preprocessor functions

        //fileInf->currLineCon;

        if(!isStrEmpty(fileInf->currLineCon))
            fprintf(desFilePtr, "@[%d,%d]%s", fileInf->currLine, fileInf->currCol, fileInf->currLineCon);

        if(fileInf->nextCol == fileInf->currCol || fileInf->nextCol == strlen(fileInf->currOLineCon)){ //Get next line only if the column is still set to 1 or if it's set to the last column in the current line

            fgets(fileInf->currLineCon, MAX_LINE_LENGTH, fileInf->filePtr); //Move to the next line!

            fileInf->currLine++;

            fileInf->currCol = 1;
            fileInf->nextCol = 1;

        }else{

            //Move the column content!
            fileInf->currLineCon = getStrPrt(fileInf->currOLineCon, fileInf->nextCol - 1, strlen(fileInf->currOLineCon), 0);

            fileInf->currCol = fileInf->nextCol;

        }

    } while(!feof(fileInf->filePtr));

}