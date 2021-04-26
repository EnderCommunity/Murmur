#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Deb(){ //Minimal debug
    printf("!!!debug");
    system("pause");
}

#include "libraries/types/String.h"
#include "libraries/types/FileContent.h"
#include "libraries/files/general.h"

#include "debug.c"

int main(int argc, char *argv[], char *envp[]){

    Debug("Started the compiler", 1);

    char *path[255];
    if (argv[1] != NULL)
        *path = argv[1];
    else
        scanf("%s", *path);

    //printf("[Debug] Received the path: \"%s\"\n", *path);
    DebugWithPath("Received the path: ", *path, 1);


    DebugWithPath("Opening the filestream of: ", *path, 1);

    FILE *fptr = files_OpenFileStream(*path);

    DebugWithPath("Getting the content of: ", *path, 1);

    FileContent fDat = files_GetAllData(fptr);

    Debug("Printing the current file content: ", 1);

    printf("dedede%sdedede", fDat.content);

    /*int i = 0;
    while(fDat.content[i] != EOF){
        printf("%c", fDat.content);
        i++;
    }*/
    /*for(int i = 0; i < fDat.length; i++){
        printf("%c", fDat.content[i]);
    }*/

    printf("\n");
    //DebugWithPath("Closing the filestream of: ", *path, 1);

    //fclose(fptr);

    DebugWithPath("Closed the filestream of: ", *path, 1);

    //free(*path);

    //#include "preprocessor/mode.h"

    //SetMode(fDat);

    Debug("Compiler still on hold.", 1);

    exit(EXIT_SUCCESS);

    return 0;
}