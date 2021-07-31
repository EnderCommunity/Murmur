#include "../lexical/token.h"
#include "../libraries/hex/hex.h"

FILE *lexFilPtr;
int kepLop = 1;

void setTknFilPtr(FILE *tmp){

    lexFilPtr = tmp;

}

void remTkn(M_Token tmp){ //Free allocated memory

    free(tmp.value);
    free(tmp.o); //Debug
    free(tmp.srcFile);

}

char* getStrSec(char *str, char *frtStr, char *lstStr){ //Get the substring between the first occurrences of `frtStr` and the last occurrence of `lstStr`

    char *tmp = malloc(strlen(str)*sizeof(char));

    strcpy(tmp, str);

    tmp = getStrPrt(tmp, getStrIndx(tmp, frtStr) + strlen(frtStr), getLstStrIndx(tmp, lstStr) + 1 - strlen(lstStr), 0);

    return tmp;

}

M_Token getTkn(){ //Get a token

    M_Token tmp;

    tmp.value = malloc(sizeof(char)*MAX_LINE_LENGTH);
    tmp.o = malloc(sizeof(char)*MAX_LINE_LENGTH); //Debug
    tmp.srcFile = malloc(sizeof(char)*MAX_PATH_LENGTH);

    fgets(tmp.value, MAX_LINE_LENGTH, lexFilPtr);

    strcpy(tmp.o, tmp.value); //Debug

    kepLop = !feof(lexFilPtr);

    if(kepLop){

        if(tmp.value[strlen(tmp.value) - 1] == '\n')
            tmp.value[strlen(tmp.value) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!
    
        tmp.type = atoi(getStrPrt(tmp.value, 0, 4, 0));

        int tmpRefIndx = getLstStrIndx(tmp.value, "`");

        int frst, scnd;

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.defVal1 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.defVal2 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.defVal3 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.defVal4 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        tmpRefIndx += 2; //Skip the " |" part!

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.adtVal1 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.adtVal2 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.adtVal3 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        frst = ++tmpRefIndx + 1;
        scnd = tmpRefIndx++ + 2;
        tmp.adtVal4 = atoi(getStrPrt(tmp.value, frst, scnd, 0)); //+2

        tmp.srcFile = getStrSec(tmp.value, "<", ">");

        tmp.srcLine = hexToInt(getStrPrt(tmp.value, getLstStrIndx(tmp.value, "0x") + 2, getLstStrIndx(tmp.value, "0x") + 2 + 9, 0));
        tmp.srcColumn = hexToInt(getStrPrt(tmp.value, getLstStrIndx(tmp.value, "1x") + 2, getLstStrIndx(tmp.value, "1x") + 2 + 9, 0));

        tmp.value = getStrSec(tmp.value, "`", "`");

    }

    return tmp;

}
