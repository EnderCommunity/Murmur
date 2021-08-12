#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../types/String.h"

static FILE* OpnStrm(char path[]){ //Open a file stream

    if(strlen(path) == 0 || (char *)path == NULL){

        perror("[Error] Received an invalid path!\n");
        exit(EXIT_FAILURE);

    }

    FILE *fptr = fopen(path, "r");

    if (fptr == NULL){

        perror("[Error] Failed to open the file.\n");
        exit(EXIT_FAILURE);

    }

    return fptr;

}

FILE* cpyFileCon(FILE *destPtr, FILE *srcPtr){

    char *str;
  
    do{

        fgets(str, MAX_LINE_LENGTH, srcPtr);

        fprintf(destPtr, "%s", str);

    }while(!feof(srcPtr));

    return destPtr;
  
}