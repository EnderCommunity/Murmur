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
    int isSptZon; //Is the current line in a separate zone?
    char *curZonId;

} FileInfo;

FileInfo* defFileDatObj(FILE* file, char *path, int isFull, char *srcPth) { //Define an object to keep track of each file's mode

    FileInfo *tmp = malloc(sizeof(FileInfo) + sizeof(char)*(MAX_PATH_LENGTH + 2*MAX_LINE_LENGTH + 12));

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
    tmp->isSptZon = 0; //Is the file is not in a separate zone!
    tmp->curZonId = malloc(sizeof(char)*12);

    fgets(tmp->currOLineCon, MAX_LINE_LENGTH, tmp->filePtr);

    if(tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] == '\n')
        tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!
    
    while(isspace(tmp->currOLineCon[0]) && strlen(tmp->currOLineCon) > 1){ //Remove the extra whitespace without losing track of the column number

        //Shif by one char
        tmp->currOLineCon = shfStr(tmp->currOLineCon, 1);

        tmp->currCol++;

    }

    strcpy(tmp->currLineCon, tmp->currOLineCon);

    if(getLstStrIndx(tmp->path, MUR_LIB_FILEEXT) == strlen(tmp->path) - 8) //A mur library file!
        tmp->mode = 'L';
    else if(getLstStrIndx(tmp->path, MUR_FILEEXT) == strlen(tmp->path) - 4) //A normal file!
        tmp->mode = 'N';

    if(ENABLE_PREPROCESSOR_HEADER && getStrIndx(tmp->currOLineCon, "#header") == 0) { //The head function is present!

        writeLogLine("Preprocessor", 0, "The header has been detected!", 0, 0, 0);

        //printf("\n00%s00", tmp->currOLineCon);

        char *tmpStr = getStrPrt(tmp->currOLineCon, 7, strlen(tmp->currOLineCon), 0);

        //printf("\n`%s`", tmpStr);

        int indx, indxShft = 0;
        while((indx = getStrIndx(tmpStr, "<")) != -1){

            int endIndx = getStrIndx(tmpStr, ">");

            if(endIndx - indx > 1){

                char *tmpSubStr = getStrPrt(tmpStr, indx + 1, endIndx, 0);

                //Check the flag
                if(strcmp(tmpSubStr, "no-comments") == 0) //No comments will get filtered!
                    ENVI_ENABLE_COMMENTS = 0;
                else if(strcmp(tmpSubStr, "no-preprocessor-methods") == 0) //The compiler will not check for preprocessor methods
                    ENVI_CHECK_FOR_PREPROCESSOR_METHODS = 0;
                else //Unknown flag!
                    rpt(REPORT_CODE_WARNING, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_PROCESS_FLAGUNKNOWN, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    tmp->currLine, //The line of this error
                    tmp->currCol + indx + 7 + indxShft); //The column the error occurs

                tmpStr = shfStr(tmpStr, endIndx + 1);
                indxShft += endIndx + 1;

                //printf("\n-%s-", tmpStr);

                free(tmpSubStr);

            }else{

                if(endIndx == -1){

                    rpt(REPORT_CODE_ERROR, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_PROCESS_FLAGCLOSINGQUOTEMISSING, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    tmp->currLine, //The line of this error
                    tmp->currCol + indx + 7 + indxShft); //The column the error occurs

                    break; //Debug

                }else{

                    rpt(REPORT_CODE_WARNING, //This is an error
                    REPORT_SECTION_PREPROCESSOR, //The error was detected by the preprocessor
                    MSG_PPC_PROCESS_FLAGEMPTY, //This is the custom error message (check /compiler/errors/messages.h)
                    srcPth, //The source of this error
                    tmp->currLine, //The line of this error
                    tmp->currCol + indx + 7 + indxShft); //The column the error occurs

                    tmpStr = shfStr(tmpStr, indx + 2);
                    indxShft += indx + 2;

                }

            }

        }

        free(tmpStr);

        writeLogLine("Preprocessor", 0, "The header flags have been processed successfully!", 0, 0, 0);

        fgets(tmp->currOLineCon, MAX_LINE_LENGTH, tmp->filePtr);

        tmp->currLine = 2;
        tmp->currCol = 1;
        tmp->nextCol = 1;

        tmp->nextCol = tmp->currCol;

        if(tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] == '\n')
            tmp->currOLineCon[strlen(tmp->currOLineCon) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

        // && strlen(tmp->currOLineCon) != 1
        while(isspace(tmp->currOLineCon[0])){ //Remove the extra whitespace without losing track of the column number

            //Shif by one char
            tmp->currOLineCon = shfStr(tmp->currOLineCon, 1);

            tmp->currCol++;

        }

    }

    strcpy(tmp->currLineCon, tmp->currOLineCon);

    return tmp;

}

void freeFileDatObj(FileInfo *tmp){

    free(tmp->currLineCon);
    free(tmp->currOLineCon);
    free(tmp->curZonId);
    free(tmp);

}