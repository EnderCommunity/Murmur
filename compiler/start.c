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

int main(int argc, char *argv[]){ //You can also use `char *envp[]`

    RegDebStr(); //Start the debuging timer

    Debug("Starting the compiler", 0);

    char path[255];
    char *pathPtr = path;

    if (argv[1] != NULL)
        strcpy(path, argv[1]);
    else{
        fgets(path, 255, stdin);
        path[strcspn(path, "\n")] = 0;
    }

    //printf("[Debug] Received the path: \"%s\"\n", *path);
    DebugWithPath("Received the path: ", path, 0);


    //DebugWithPath("Opening the filestream of: ", path, 0);

    /*FILE *fptr = files_OpenFileStream(pathPtr); //This is garbage

    //DebugWithPath("Getting the content of: ", pathPtr, 0);

    FileContent *fDat = files_GetAllData(fptr);

    Debug("Printing the current file content: ", 1);

    printf("dedede%sdedede", *(fDat->con));

    /*int i = 0;
    while(fDat.content[i] != EOF){
        printf("%c", fDat.content);
        i++;
    }*/
    /*for(int i = 0; i < fDat.length; i++){
        printf("%c", fDat.content[i]);
    }*/

    //printf("\n");
    //DebugWithPath("Closing the filestream of: ", *path, 1);

    //fclose(fptr);

    //DebugWithPath("Closed the filestream of: ", pathPtr, 1);

    //free(*path);

    //#include "preprocessor/mode.h"

    //SetMode(fDat);

    RegDebEnd(); //End the debuging timer

    Debug("Compiler still on hold.", 1);

    //exit(EXIT_SUCCESS);

    return 0;
}