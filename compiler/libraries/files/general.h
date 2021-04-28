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

/*static FileContent* files_GetAllData(FILE *fptr){ //Get the data of a file

    FileContent *data;
    int len = 0;
    char *con;
    char currChar;

    while((currChar = fgetc(fptr)) != EOF)
        con[len++] = currChar;

    con[len++] = '\0';

    //_Str *str = defStr('L');

    //setStrVal(str, con);
    //printf("%s", getStrVal(str));

    //Deb();
    //realloc(&data, sizeof(FileContent) + (str->len - 1)*sizeof(char));
    
    //Deb();
    //realloc(&(data.content), (str->len)*sizeof(char));

    //Deb();
    //setStrVal(data.content, *str->con);

    //Deb();
    //data->con = (_Str *)defStr('L');
    setStrVal(data->con, con); //Crash!

    //str;

    //Deb();
    //printf("%s", getStrVal(data.content));

    //Deb();
    //free(con);

    return data;

    //free(data.content);
}*/