#include <stdio.h>
#include <stdlib.h>

struct FileContent {
    char *content;
    int length;
};

FILE* files_OpenFileStream(char path[]){

    FILE *fptr = fopen(path, "r");

    if (fptr == NULL){
        perror("[Error] Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }

    return fptr;
}

struct FileContent files_GetAllData(FILE *fptr){

    struct FileContent data;

    data.content = (char *)calloc(1, sizeof(char));

    data.length = 0;

    char currChar;

    while((currChar = fgetc(fptr)) != EOF)
        data.content[data.length++] = currChar;

    data.content[data.length+1] = '\0';

    return data;

    //free(data.content);
}