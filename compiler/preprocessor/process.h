#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char mode; //A file's mode can be set to 'N' (Normal), 'M' (Module), 'U' (Unknown), or 'S' (Skip)
    int isFull; //Is this the main file, or what?
    char *path; //The path of the file
    FILE *filePtr; //The file pointer, it should always point to the current line that is being processed
    FILE *fileStrPtr; //The file pointer, it should always point to the first line of the file
    char *currLineCon;
} FileInfo;

FileInfo* defFileDatObj(FILE* file, char *path, int isFull) { //Define an object to keep track of each file's mode
    FileInfo *tmp = malloc(sizeof(FileInfo) + sizeof(char)*(254 + 508));
    tmp->path = malloc(sizeof(char)*255); //The max path length is 255 characters
    tmp->path = path;
    tmp->currLineCon = malloc(sizeof(char)*509);
    tmp->filePtr = file;
    tmp->fileStrPtr = file;
    tmp->isFull = isFull; //Is this a full compiling process?
    tmp->mode = 'N';
    fgets(tmp->currLineCon, 509, tmp->filePtr);
    //printf("\nPath String: %s\n", tmp->path);
    //printf("\nPath Len: %d\n", strlen(tmp->path));
    //printf("\nPath `.esf` index: %d\nPath `.esmf` index: %d\n", getStrIndx((tmp->path), ".esf"), getStrIndx(tmp->path, ".esmf"));
    if(getStrIndx(tmp->path, ".esf") == strlen(tmp->path) - 4) //A normal file!
        tmp->mode = 'N';
    else if(getStrIndx(tmp->path, ".esmf") == strlen(tmp->path) - 5) //A module file!
        tmp->mode = 'M';
    else //This will result in an error!!!!
        tmp->mode = 'U';
    if(getStrIndx(tmp->currLineCon, "##head") == 0) { //The head function is present!
        if(inStrRng(tmp->currLineCon, "--skip")) //This file will be skipped!
            tmp->mode = 'S';
    }
    return tmp;
}

FileInfo* reallocCurrLin(FileInfo *tmp){
    free(tmp->currLineCon);
    tmp->currLineCon = malloc(sizeof(char)*509);
    return tmp;
}
