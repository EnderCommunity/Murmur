#include "../lexical/token.h"
#include "../libraries/hex/hex.h"

FILE *lexFilPtr;
int kepLop = 1;

void setTknFilPtr(FILE *tmp){

    lexFilPtr = tmp;

}

void remTkn(M_Token tmp){ //Free allocated memory

    free(tmp.val);
    free(tmp.srcFil);

}

char* getStrSec(char *str, char *frtStr, char *lstStr){ //Get the substring between the first occurrences of `frtStr` and the last occurrence of `lstStr`

    char *tmpStr = getStrPrt(str, getStrIndx(str, frtStr) + strlen(frtStr), getLstStrIndx(str, lstStr) + 1 - strlen(lstStr), 0);

    return tmpStr;

}

int getNxtLinUniVal(char *lin, int *tmp){ //Get a the next one digit value from the current line

    int frt = ++(*tmp) + 1;
    int snd = (*tmp)++ + 2;

    char *tmpStr = getStrPrt(lin, frt, snd, 0);
    int rslt = atoi(tmpStr);

    free(tmpStr);

    return rslt; //+2

}

M_Token getTkn(){ //Get a token

    M_Token tmp;

    tmp.val = malloc(sizeof(char)*(MAX_LINE_LENGTH + 1));
    //tmp.srcFile = malloc(sizeof(char)*(MAX_PATH_LENGTH + 1));

    fgets(tmp.val, MAX_LINE_LENGTH, lexFilPtr);

    kepLop = !feof(lexFilPtr);

    if(kepLop){

        printf("%s", tmp.val); //Debug

        if(tmp.val[strlen(tmp.val) - 1] == '\n')
            tmp.val[strlen(tmp.val) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

        char *tmpTypStr = getStrPrt(tmp.val, 0, 4, 0);
    
        tmp.typ = atoi(tmpTypStr);

        free(tmpTypStr);

        int tmpRefIndx = getLstStrIndx(tmp.val, "`");

        tmp.defVal1 = getNxtLinUniVal(tmp.val, &tmpRefIndx);
        tmp.defVal2 = getNxtLinUniVal(tmp.val, &tmpRefIndx);
        tmp.defVal3 = getNxtLinUniVal(tmp.val, &tmpRefIndx);
        tmp.defVal4 = getNxtLinUniVal(tmp.val, &tmpRefIndx);

        tmpRefIndx += 2; //Skip the " |" part!

        tmp.adtVal1 = getNxtLinUniVal(tmp.val, &tmpRefIndx);
        tmp.adtVal2 = getNxtLinUniVal(tmp.val, &tmpRefIndx);
        tmp.adtVal3 = getNxtLinUniVal(tmp.val, &tmpRefIndx);
        tmp.adtVal4 = getNxtLinUniVal(tmp.val, &tmpRefIndx);

        tmp.srcFil = getStrSec(tmp.val, "[", "]");

        tmp.srcLin = hexToInt(getStrPrt(tmp.val, getLstStrIndx(tmp.val, "0x") + 2, getLstStrIndx(tmp.val, "0x") + 2 + 9, 0));
        tmp.srcCol = hexToInt(getStrPrt(tmp.val, getLstStrIndx(tmp.val, "1x") + 2, getLstStrIndx(tmp.val, "1x") + 2 + 9, 0));


        char *tmpValStr = getStrSec(tmp.val, "`", "`");

        free(tmp.val);

        tmp.val = tmpValStr;

    }else
        free(tmp.val);

    return tmp;

}
