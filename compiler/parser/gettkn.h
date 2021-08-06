#include "../lexical/token.h"
#include "../libraries/hex/hex.h"

FILE *lexFilPtr;
int kepLop = 1;

void setTknFilPtr(FILE *tmp){

    lexFilPtr = tmp;

}

void remTkn(M_Token tmp){ //Free allocated memory

    free(tmp.value);
    free(tmp.srcFile);

}

char* getStrSec(char *str, char *frtStr, char *lstStr){ //Get the substring between the first occurrences of `frtStr` and the last occurrence of `lstStr`

    char *tmp = malloc((strlen(str) + 1)*sizeof(char));

    strcpy(tmp, str);

    tmp = getStrPrt(tmp, getStrIndx(tmp, frtStr) + strlen(frtStr), getLstStrIndx(tmp, lstStr) + 1 - strlen(lstStr), 0);

    return tmp;

}

int getNxtLinUniVal(char *lin, int *tmp){ //Get a the next one digit value from the current line

    int frt = ++*tmp + 1;
    int snd = *tmp++ + 2;

    return atoi(getStrPrt(lin, frt, snd, 0)); //+2

}

M_Token getTkn(){ //Get a token

    M_Token tmp;

    tmp.value = malloc(sizeof(char)*(MAX_LINE_LENGTH + 1));
    tmp.srcFile = malloc(sizeof(char)*(MAX_PATH_LENGTH + 1));

    fgets(tmp.value, MAX_LINE_LENGTH, lexFilPtr);

    kepLop = !feof(lexFilPtr);

    if(kepLop){

        printf("%s", tmp.value); //Debug

        if(tmp.value[strlen(tmp.value) - 1] == '\n')
            tmp.value[strlen(tmp.value) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!
    
        tmp.type = atoi(getStrPrt(tmp.value, 0, 4, 0));

        int tmpRefIndx = getLstStrIndx(tmp.value, "`");

        tmp.defVal1 = getNxtLinUniVal(tmp.value, &tmpRefIndx);
        tmp.defVal2 = getNxtLinUniVal(tmp.value, &tmpRefIndx);
        tmp.defVal3 = getNxtLinUniVal(tmp.value, &tmpRefIndx);
        tmp.defVal4 = getNxtLinUniVal(tmp.value, &tmpRefIndx);

        tmpRefIndx += 2; //Skip the " |" part!

        tmp.adtVal1 = getNxtLinUniVal(tmp.value, &tmpRefIndx);
        tmp.adtVal2 = getNxtLinUniVal(tmp.value, &tmpRefIndx);
        tmp.adtVal3 = getNxtLinUniVal(tmp.value, &tmpRefIndx);
        tmp.adtVal4 = getNxtLinUniVal(tmp.value, &tmpRefIndx);

        tmp.srcFile = getStrSec(tmp.value, "<", ">");

        tmp.srcLine = hexToInt(getStrPrt(tmp.value, getLstStrIndx(tmp.value, "0x") + 2, getLstStrIndx(tmp.value, "0x") + 2 + 9, 0));
        tmp.srcColumn = hexToInt(getStrPrt(tmp.value, getLstStrIndx(tmp.value, "1x") + 2, getLstStrIndx(tmp.value, "1x") + 2 + 9, 0));

        tmp.value = getStrSec(tmp.value, "`", "`");

    }

    return tmp;

}
