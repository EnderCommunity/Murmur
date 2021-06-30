void movCnt(FileInfo *fileInf, FILE *desFilePtr){

    writeLogLine("Preprocessor", 0, "Copying file content...", 0, 0, 0);

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

        if(!isStrEmpty(fileInf->currLineCon))
            fprintf(desFilePtr, fileInf->currLineCon);

        if(keepLoop){

            fgets(fileInf->currOLineCon, MAX_LINE_LENGTH, fileInf->filePtr);

            if(wait)
                keepLoop = !feof(fileInf->filePtr);

            if(!wait)
                keepLoop = 0;

            if(!keepLoop && wait){
                keepLoop = 1;
                wait = 0;
            }

            if(keepLoop){

                strcpy(fileInf->currLineCon, fileInf->currOLineCon);

            }
        }

    }

}