/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* files_GetLines(char *fCon){

    int r = 0, c = 0, cou = 0;
    int *linBr = (int *)malloc(sizeof(int));
    char currChar;

    while((currChar = fCon[cou]) != EOF){
        printf("%c", currChar);
        if(currChar == '\n'){
            r++;
            realloc(linBr, r*sizeof(int));
            linBr[r-1] = c;
            c = 0;
        }
        c++;
        cou++;
    }

    return linBr;
}*/