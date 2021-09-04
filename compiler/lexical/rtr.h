#include "../lexical/token.h"

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

M_Token rtrLxrDat(char *val, int lin){

    M_Token tmp; // A lexer token

    tmp.__srcLinLen = strlen(val);
    tmp.__ahd_filEnd = 0;

    if(val[strlen(val) - 1] == '\n')
        val[strlen(val) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

    char *tmpTypStr = getStrPrt(val, 0, 4, 0);
    
    tmp.typ = atoi(tmpTypStr);

    free(tmpTypStr);

    int tmpRefIndx = getLstStrIndx(val, "`");

    tmp.__srcLin = lin;

    tmp.defVal1 = getNxtLinUniVal(val, &tmpRefIndx);
    tmp.defVal2 = getNxtLinUniVal(val, &tmpRefIndx);
    tmp.defVal3 = getNxtLinUniVal(val, &tmpRefIndx);
    tmp.defVal4 = getNxtLinUniVal(val, &tmpRefIndx);

    tmpRefIndx += 2; //Skip the " |" part!

    tmp.adtVal1 = getNxtLinUniVal(val, &tmpRefIndx);
    tmp.adtVal2 = getNxtLinUniVal(val, &tmpRefIndx);
    tmp.adtVal3 = getNxtLinUniVal(val, &tmpRefIndx);
    tmp.adtVal4 = getNxtLinUniVal(val, &tmpRefIndx);

    tmp.srcFil = getStrSec(val, "[", "]");

    tmp.srcLin = hexToInt(getStrPrt(val, getLstStrIndx(val, "0x") + 2, getLstStrIndx(val, "0x") + 2 + 9, 0));
    tmp.srcCol = hexToInt(getStrPrt(val, getLstStrIndx(val, "1x") + 2, getLstStrIndx(val, "1x") + 2 + 9, 0));

    tmp.val = getStrSec(val, "`", "`");

    return tmp;

}