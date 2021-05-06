#include <ctype.h>

int getChrIndx(char *str, char chr){ //Get the index of a char in a string

    int indx = (int)((char *)strchr(str, chr) - str);

    return indx >= 0 ? indx : -1;

}

int getStrIndx(char *str, char *strForChk){ //Get the index of a string in a string (weird behaviour has been noticed)

    int indx = strstr(str, strForChk) - str;

    return indx >= 0 ? indx : -1;

}

int getLstStrIndx(char *str, char *strForChk){ //Get the index of the last appearance of a string inside a string

    int lIndx, mIndx = -1;

    do{

        lIndx = mIndx;
        mIndx = getStrIndx(str, strForChk);

        str += lIndx - mIndx + strlen(strForChk);

    } while(mIndx != -1);

    return lIndx;
}

int inStrRng(char *str, char *strForChk){ //Check if a string exists inside a string

    return strstr(str, strForChk) != NULL;

}

char* apdStr(char *dest, char *str){ //Append two stings

    char* rslt = calloc(strlen(dest) + strlen(str), sizeof(char));

    strcpy(rslt, dest);
    strcat(rslt, str);

    return rslt;

}

char* newStr(int size) { //Create a new string

    char * tmp = malloc(sizeof(char)*size);

    tmp[0] = '\0';

    return tmp;

}

char* rszStr(char *str, int size) { //Resize a string

    str = realloc(str, sizeof(char)*size);

    return str;

}

char* getStrPrt(char *str, int strIndx, int endIndx, int endLine) { //Get a part from a string
    /*if(strIndx == endIndx){
        //Throw an error!
    }else */if(endIndx > strlen(str) || endIndx < strIndx){
        //Throw an error!
    }else if(strIndx > strlen(str) || strIndx < 0){
        //Throw an error!
    }else{
        char *nStr = malloc((endIndx - strIndx + 2 + (endLine ? 1 : 0))*sizeof(char));
        for(int i = 0; strIndx <= endIndx; strIndx++, i++){
            nStr[i] = str[strIndx];
            if(endIndx == strIndx){
                if(endLine)
                    nStr[++i] = '\n';
                nStr[++i] = '\0';
            }
        }
        str = nStr;
    }

    return str;

}

int numOfCharInStr(char *str, char cha){ //Get the number of times a char appeared in a string

    int n = 0;

    for(int i = 0; i < sizeof(str); i++)
        if(str[i] == cha)
            n++;

    return n;

}

char* remCharFromStr(char *str, char cha){ //Remove a char from the string

    char *nStr = malloc((strlen(str) - numOfCharInStr(str, cha) + 1)*sizeof(char));

    memset(nStr, 0x00, (strlen(str) - numOfCharInStr(str, cha) + 1)*sizeof(char)); //Clear the new memory

    for(int i = 0, c = 0; i < strlen(str); i++){

        if(str[i] != cha){
            nStr[c] = str[i];
            c++;
        }

        if(i == strlen(str) - 1)
            nStr[++c] = '\0';

    }

    return nStr;

}

char* remStrFromStr(char *str, char *sub){ //Remove a part from the string

    char *p, *q, *r;

    if((q = r = strstr(str, sub)) != NULL){

        size_t len = strlen(sub);

        while((r = strstr(p = r + len, sub)) != NULL){
            memmove(q, p, r - p);
            q += r - p;
        }

        memmove(q, p, strlen(p) + 1);

    }

    return str;

}

int isStrEmpty(char *str){

    int whiSpc = 0;

    for(int i = 0; str[i] != '\0'; i++)
        if(isspace(str[i]) || str[i] == '\n' || str[i] == '\t' || str[i] == '\0' || str[i] == '\a' || str[i] == '\b' || str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
            whiSpc++;

    return whiSpc == strlen(str);

}