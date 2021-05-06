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
    fileInf->path;
    fileInf->filePtr;
    fileInf->fileStrPtr;
    fileInf->currLine;
    fileInf->currCol;

    do {

        fileInf = chkForCom(fileInf);
        fileInf = chkForPprFunc(fileInf);

        //fileInf->currLineCon;

        if(!isStrEmpty(fileInf->currLineCon))
            fprintf(desFilePtr, "@[%d,%d]%s", fileInf->currLine, fileInf->currCol, fileInf->currLineCon);

        if(fileInf->currCol == 1) //This can break easily!
            fgets(fileInf->currLineCon, MAX_LINE_LENGTH, fileInf->filePtr); //Move to the next line!

        fileInf->currLine++;

    } while(!feof(fileInf->filePtr));

}