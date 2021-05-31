#include <stdio.h>
#include <stdlib.h>

typedef struct{

    char mode; //A file's mode can be set to 'N' (Normal), 'M' (Module), 'U' (Unknown), or 'S' (Skip)
    int isFull; //Is this the main file, or what?
    char *path; //The path of the file
    FILE *filePtr; //The file pointer, it should always point to the current line that is being processed
    FILE *fileStrPtr; //The file pointer, it should always point to the first line of the file
    int currLine;
    int currCol;
    int nextCol;
    char *currLineCon;
    char *currOLineCon;

} FileInfo;

FileInfo* defFileDatObj(FILE* file, char *path, int isFull) { //Define an object to keep track of each file's mode

    FileInfo *tmp = malloc(sizeof(FileInfo) + sizeof(char)*(MAX_PATH_LENGTH + MAX_LINE_LENGTH - 2));

    tmp->path = malloc(sizeof(char)*MAX_PATH_LENGTH); //The max path length is 255 characters
    tmp->path = path;
    tmp->currLineCon = malloc(sizeof(char)*MAX_LINE_LENGTH);
    tmp->currOLineCon = malloc(sizeof(char)*MAX_LINE_LENGTH);
    tmp->filePtr = file;
    tmp->fileStrPtr = file;
    tmp->isFull = isFull; //Is this a full compiling process?
    tmp->mode = 'N';
    tmp->currLine = 1;
    tmp->currCol = 1;
    tmp->nextCol = 1;

    fgets(tmp->currOLineCon, MAX_LINE_LENGTH, tmp->filePtr);
    strcpy(tmp->currLineCon, tmp->currOLineCon);

    if(getLstStrIndx(tmp->path, ".esf") == strlen(tmp->path) - 4) //A normal file!
        tmp->mode = 'N';
    else if(getLstStrIndx(tmp->path, ".esmf") == strlen(tmp->path) - 5) //A module file!
        tmp->mode = 'M';
    else //This will result in an error!!!!
        tmp->mode = 'U';

    if(getStrIndx(tmp->currOLineCon, "##head") == 0) { //The head function is present!

        if(ENABLE_PREPROCESSOR_SKIP_FLAG & inStrRng(tmp->currOLineCon, "--skip")) //This file will be skipped!
            tmp->mode = 'S';
    }

    return tmp;

}

FileInfo* reallocCurrLin(FileInfo *tmp){

    free(tmp->currLineCon);
    tmp->currLineCon = malloc(sizeof(char)*509);

    return tmp;

}
