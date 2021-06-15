#include "envi.h"
#include "predef.h"
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
#include "libraries/paths/paths.h"

#include "workstation.c"

#include "debug.c"
#include "log.c"

void preprocess(FILE *filePtr, char *path, int isFull, FILE *desFilePtr);

int main(int argc, char *argv[]){ //You can also use `char *envp[]`

    RegDebStr(); //Start the debugging timer

    srand(time(NULL)); //Randomise the number generator output

    Debug("Starting the compiler", 0);

    char path[255];
    char *pathPtr = path;

    if (argc != 0){

        strcpy(path, argv[1]);

        path[strlen(path)] = '\0'; //Make sure a string-end char is always at the end of this environment variable

    }else{

        fgets(path, 255, stdin);

        path[strcspn(path, "\n") - 1] = '\0'; //Make sure to replace the new line char with a string-end char

    }

    //Get the path of the folder that contains the current file

    DebugWithPath("Received the path: ", path, 0);

    //Start a workstation
    setupWrkstn(pathPtr);

    printf("\n Workstation Path: \"%s\"\nWorkstation Name: \"%s\"\n", wrkstn.Path, wrkstn.Name);

    //Start logging the session
    newLogFile(apdStr(wrkstn.Path, apdStr(wrkstn.Name, ".log")));

    writeLogLine("Compiler Manager", 0, "Testing the `writeLogLine` function", 0, 0, 0);

    FILE *mainFilePtr = OpnStrm(path);

    FILE *tmpFilePtr = genFilStr(apdStr(wrkstn.Path, wrkstn.Name)); //Create a temporary file for the compiling process
    //There should be only one file per process
    //Note: the generated files will get deleted automatically in the future, unless the 'OUTPUT_TEMP_FILE' environment variable is set to 'true'/'1'

    writeLogLine("Compiler Manager", 0, "Starting the preprocessor.", 0, 0, 0);
    preprocess(mainFilePtr, path, 1, tmpFilePtr); //Initiate the compiling process

    fclose(mainFilePtr);
    fclose(tmpFilePtr);

    writeLogLine("Compiler Manager", 0, "Closed all files sessions.", 0, 0, 0);

    RegDebEnd(); //End the debugging timer

    Deb();

    //exit(EXIT_SUCCESS);

    writeLogLine("Compiler Manager", 0, "Task finished successfully! (Ending process)", 0, 0, 0);

    return 0;

}

#include "preprocessor/checker.h"
#include "preprocessor/reader.h"


void preprocess(FILE *filePtr, char *path, int isFull, FILE *desFilePtr){ //Compile a file and it's content

    writeLogLine("Preprocessor", 0, "Preprocessor started!", 0, 0, 0);

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

    if(fileInf->mode == 'S'){
        writeLogLine("Preprocessor", 0, "The skip flag has been detected! (Skipping to the final stage)", 0, 0, 0);
    }else{
        ppcRead(fileInf, desFilePtr); //Let the preprocessor do it's thing!
    }

    //desFileStrPtr; //This file should have all the needed code, preprocessed, with no comments!

    //You can start to parse this file!

}