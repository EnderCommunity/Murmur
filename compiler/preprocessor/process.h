#include <stdio.h>
#include <stdlib.h>

typedef struct{

    char mode; //A file's mode can be set to 'N' (Normal), 'L' (Library), or 'U' (Unknown)
    int isFull; //Is this the main file, or what?
    char *path; //The path of the file
    FILE *filePtr; //The file pointer, it should always point to the current line that is being processed
    FILE *fileStrPtr; //The file pointer, it should always point to the first line of the file
    int currLine;
    int currCol;
    int nextCol;
    char *currLineCon;
    char *currOLineCon;
    int curZon; //The current file local zone (root-level, group-level, class-level, etc)

} FileInfo;

FileInfo* defFileDatObj(FILE* file, char *path, int isFull) { //Define an object to keep track of each file's mode

    FileInfo *tmp = malloc(sizeof(FileInfo) + sizeof(char)*(MAX_PATH_LENGTH + 2*MAX_LINE_LENGTH));

    //memset(tmp, 0x00, sizeof(FileInfo) + sizeof(char)*(MAX_PATH_LENGTH + 2*MAX_LINE_LENGTH - 2)); //Clear the new memory

    //tmp->path = malloc(sizeof(char)*MAX_PATH_LENGTH); //The max path length is 255 characters
    tmp->path = path;
    tmp->currLineCon = malloc(sizeof(char)*MAX_LINE_LENGTH);
    memset(tmp->currLineCon, 0x00, sizeof(char)*MAX_LINE_LENGTH);
    tmp->currOLineCon = malloc(sizeof(char)*MAX_LINE_LENGTH);
    memset(tmp->currOLineCon, 0x00, sizeof(char)*MAX_LINE_LENGTH);
    tmp->filePtr = file;
    tmp->fileStrPtr = file;
    tmp->isFull = isFull; //Is this a full compiling process?
    tmp->mode = 'U';
    tmp->currLine = 1;
    tmp->currCol = 1;
    tmp->nextCol = 1;
    tmp->curZon = 0; //Is the file current in the root zone of the code

    fgets(tmp->currOLineCon, MAX_LINE_LENGTH, tmp->filePtr);

    strcpy(tmp->currLineCon, tmp->currOLineCon);

    if(getLstStrIndx(tmp->path, ".mur") == strlen(tmp->path) - 4) //A normal file!
        tmp->mode = 'N';
    else if(getLstStrIndx(tmp->path, ".lib.mur") == strlen(tmp->path) - 8) //A mur library file!
        tmp->mode = 'L';

    if(ENABLE_PREPROCESSOR_HEADER && getStrIndx(tmp->currOLineCon, "#head") == 0) { //The head function is present!

        writeLogLine("Preprocessor", 0, "The header has been detected!", 0, 0, 0);

        if(inStrRng(tmp->currOLineCon, "<no-comments>")) //No comments will get filtered!
            ENVI_ENABLE_COMMENTS = 0;

        if(inStrRng(tmp->currOLineCon, "<no-preprocessor-methods>")) //The compiler will not check for preprocessor methods
            ENVI_CHECK_FOR_PREPROCESSOR_METHODS = 0;
        
        if((ENABLE_ALLOW_SEPARATE_FLAG && inStrRng(tmp->currOLineCon, "<allow-separate>")) || tmp->mode == 'L')
            ENVI_ENABLE_SEPARATE_METHOD = 1;

        writeLogLine("Preprocessor", 0, "The header flags have been processed successfully!", 0, 0, 0);

        fgets(tmp->currOLineCon, MAX_LINE_LENGTH, tmp->filePtr);

        tmp->currLine = 2;
        tmp->currCol = 1;
        tmp->nextCol = 1;

        if(tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] == '\n')
            tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

        while(isspace(tmp->currOLineCon[0])){ //Remove the extra whitespace without losing track of the column number

            //Shif by one char
            tmp->currOLineCon = shfStr(tmp->currOLineCon, 1);

            tmp->currCol++;

        }

        tmp->nextCol = tmp->currCol;

        strcpy(tmp->currLineCon, tmp->currOLineCon);

    }else{

        if(tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] == '\n')
            tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

        strcpy(tmp->currLineCon, tmp->currOLineCon);

    }

    return tmp;

}

void freeFileDatObj(FileInfo *tmp){

    free(tmp->currLineCon);
    free(tmp->currOLineCon);
    free(tmp);

}

/*FileInfo* reallocCurrLin(FileInfo *tmp){

    free(tmp->currLineCon);
    tmp->currLineCon = malloc(sizeof(char)*509);

    return tmp;

}*/
