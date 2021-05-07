#include "envi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Deb(){ //Minimal debug

    printf("[Debug] ");
    system("pause");

}

#include "libraries/types/String.h"
//#include "libraries/types/FileContent.h"
#include "libraries/files/general.h"
#include "libraries/files/gen.c"

#include "debug.c"

void preprocess(FILE *filePtr, char *path, int isFull, FILE *desFilePtr);

int main(int argc, char *argv[]){ //You can also use `char *envp[]`

    RegDebStr(); //Start the debugging timer

    srand(time(NULL));

    Debug("Starting the compiler", 0);

    char path[255];
    char *pathPtr = path;

    if (argv[1] != NULL)
        strcpy(path, argv[1]);
    else{
        fgets(path, 255, stdin);
        path[strcspn(path, "\n")] = 0;
    }

    DebugWithPath("Received the path: ", path, 0);

    FILE *mainFilePtr = OpnStrm(path);

    FILE *tmpFilePtr = genFilStr(); //Create a temporary file for the compiling process
    //There should be only one file per process

    preprocess(mainFilePtr, path, 1, tmpFilePtr); //Initiate the compiling process

    fclose(mainFilePtr);
    fclose(tmpFilePtr);

    RegDebEnd(); //End the debugging timer

    Deb();

    //exit(EXIT_SUCCESS);

    return 0;

}

#include "preprocessor/checker.h"
#include "preprocessor/reader.h"


void preprocess(FILE *filePtr, char *path, int isFull, FILE *desFilePtr){ //Compile a file and it's content

    FILE *desFileStrPtr = desFilePtr; //Save the start pointer!

    //desFilePtr; //This file should be used to store all the code that will be compiled in the process

    FileInfo *fileInf = checkFlags(filePtr, path, isFull); //A object that contains the file info!

    printf("\n[Debug] Mode: %c\n", fileInf->mode);
    printf("[Debug] Is Full: %d\n", fileInf->isFull);
    printf("[Debug] Current Line Content: %s\n", fileInf->currLineCon);
    printf("[Debug] Current Line Original Content: %s\n", fileInf->currOLineCon);
    printf("[Debug] Path: %s\n", fileInf->path);
    //fileInf->filePtr;
    //fileInf->fileStrPtr;

    ppcRead(fileInf, desFilePtr); //Let the preprocessor do it's thing!

    //desFileStrPtr; //This file should have all the needed code, preprocessed, with no comments!

    //You can start to parse this file!

}