#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libraries/files/general.h"

int main(int argc, char *argv[], char *envp[]){
    printf("[Debug] Started the compiler\n");

    char *path[255];
    if (argv[1] != NULL)
        *path = argv[1];
    else
        scanf("%s", *path);

    printf("[Debug] Received the path: \"%s\"\n", *path);

    if(strlen(*path) == 0){
        perror("[Error] Received an invalid path!\n");
        exit(EXIT_FAILURE);
    }

    //[START] Get the content of the file

    FILE *fptr = files_OpenFileStream(*path);

    struct FileContent fDat = files_GetAllData(fptr);

    printf("[Debug] The current file content:\n");

    for(int i = 0; i < fDat.length; i++){
        printf("%c", fDat.content[i]);
    }

    fclose(fptr);
    //[END] Get the content of the file

    printf("\n\n[Debug] Compiler still opened. Press enter to close the compiler.\n");

    getchar(); //Debug

    return 0;
}