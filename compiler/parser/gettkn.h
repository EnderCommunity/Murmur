#include "../lexical/token.h"

FILE *lexFilPtr;
int kepLop = 1;

void setTknFilPtr(FILE *tmp){

    lexFilPtr = tmp;

}

void remTkn(M_Token tmp){ //Free allocated memory

    free(tmp.value);
    free(tmp.srcFile);

}

M_Token getTkn(){ //Get a token

    M_Token tmp;

    tmp.value = malloc(sizeof(char)*MAX_LINE_LENGTH);
    tmp.srcFile = malloc(sizeof(char)*MAX_PATH_LENGTH);

    fgets(tmp.value, MAX_LINE_LENGTH, lexFilPtr);

    kepLop = !feof(lexFilPtr);

    if(tmp.value[strlen(tmp.value) - 1] == '\n')
        tmp.value[strlen(tmp.value) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

    tmp.type; //int
    tmp.value; //char*
    tmp.defVal1; //int
    tmp.defVal2; //int
    tmp.defVal3; //int
    tmp.defVal4; //int
    tmp.adtVal1; //int
    tmp.adtVal2; //int
    tmp.adtVal3; //int
    tmp.adtVal4; //int
    tmp.srcFile; //char*
    tmp.srcLine; //int
    tmp.srcColumn; //int

    return tmp;

}
