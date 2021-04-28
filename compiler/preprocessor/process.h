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
    printf("%d\n%d\n", getStrIndx(path, ".esf"), getStrIndx(path, ".esmf"));
    if(getStrIndx(path, ".esf") == strlen(path) - 5)
        tmp->mode = 'M';
    else if(getStrIndx(path, ".esmf") == strlen(path) - 6)
        tmp->mode = 'M';
    else
        tmp->mode = 'U';
    if(getStrIndx(tmp->currLineCon, "##EnderScript") == 0){
        if(inStrRng(tmp->currLineCon, "--skip"))
            tmp->mode = 'S';
    }
    return tmp;
}

FileInfo* reallocCurrLin(FileInfo *tmp){
    free(tmp->currLineCon);
    tmp->currLineCon = malloc(sizeof(char)*509);
    return tmp;
}
