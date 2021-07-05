#include <ctype.h>

int getChrIndx(char *str, char chr){ //Get the index of a char in a string

    int indx = (int)((char *)strchr(str, chr) - str);

    return indx >= 0 ? indx : -1;

}

int getStrIndx(char *str, char *strForChk){ //Get the index of a string in a string (weird behaviour has been noticed)

    int indx = strstr(str, strForChk) - str;
    //int indx = strlen(str) - strlen(strstr(str, strForChk)) + 1;
    //int indx = strlen(str) - strlen(strstr(str, strForChk));

    return indx >= 0 ? indx : -1;

}

char* getStrPrt(char *str, int strIndx, int endIndx, int endLine) { //Get a part from a string

    int s = (((endIndx - strIndx != 0) ? endIndx - strIndx : 1) + 2 + (endLine ? 1 : 0))*sizeof(char);
    char *nStr = malloc(s);

    memset(nStr, 0x00, s); //Clear the new memory

    if((endIndx > strlen(str) || endIndx < strIndx) || (strIndx < 0 || strIndx > strlen(str))){

        //Throw an error!
        writeLogLine("Library Component", 2, "ERROR", 0, 0, 0);
        exit(-1);

    }else{

        int i;

        for(i = 0; strIndx < endIndx; strIndx++, i++)
            nStr[i] = str[strIndx];

        if(endLine)
            nStr[++i] = '\n';

        nStr[++i] = '\0';

    }


    /*Deb();
    printf("--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------");
    printf("@@%s@@", nStr);
    printf("--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------\n--------------------------------------------------------");*/

    return nStr;

}

char* apdStr(char *dest, char *str){ //Append two stings

    char* rslt = malloc((strlen(dest) + strlen(str) + 1)*sizeof(char));

    strcpy(rslt, dest);
    strcat(rslt, str);

    rslt[strlen(rslt)] = '\0';

    return rslt;

}

char* remStrPrt(char *str, char *strForRem) { //Remove a part of a string (Unintended behaviours noticed, new fix)

    int indx = getStrIndx(str, strForRem);

    return (indx == -1) ?
        str
        :
        ((indx != 0) ?
            apdStr(getStrPrt(str, 0, indx - 1, 0), getStrPrt(str, indx + strlen(strForRem), strlen(str), 0))
            :
            getStrPrt(str, strlen(strForRem), strlen(str), 0))
        ;

}

char* genFillStr(int len){

    char *nStr = malloc((len + 1)*sizeof(char));

    memset(nStr, 0x00, (len + 1)*sizeof(char)); //Clear the new memory

    for(int i = 0; i < len; i++)
        nStr[i] = FILLER_STRING_CHAR;
    nStr[len] = '\0';

    return nStr;

}

char* shfStr(char *str, int n){ //Shif a string to the left by 'n' chars!

    int i, l = strlen(str);

    for(i = n; i < l; i++)
        str[i - n] = str[i];

    str[l - n] = '\0';

    return str;

    /*int l = strlen(str);

    char *tmp = malloc(sizeof(char)*(strlen(str) - n + 1)); //This ain't good...

    for(int i = n; i <= l; i++)
        tmp[i - n] = str[i];

    return tmp;*/


}

int inStrRng(char *str, char *strForChk){ //Check if a string exists inside a string

    return strstr(str, strForChk) != NULL;

}

int getLstStrIndx(char *str, char *strForChk){ //Get the index of the last appearance of a string inside a string

    /*for(int tmp = getStrIndx(str, strForChk); tmp != -1; tmp = getStrIndx(str, strForChk)){

        indx += tmp + l;

        str = shfStr(str, tmp + l);
        printf("\n%s", str);
        //str = getStrPrt(str, tmp + strlen(strForChk), strlen(str), 0);

    }

    indx -= l - 1;*/

    char *tmpStr = malloc(strlen(str)*sizeof(char));
    strcpy(tmpStr, str);

    int indx = -1,
        l = strlen(strForChk),
        tmp = getStrIndx(str, strForChk),
        kepLop = inStrRng(str, strForChk);

    while(kepLop){

        tmp = getStrIndx(str, strForChk);

        indx += tmp + l;

        str = shfStr(str, tmp + l);
        //printf("\n%s", str);

        kepLop = inStrRng(str, strForChk);

    }

    strcpy(str, tmpStr);
    free(tmpStr);

    return indx - (l - 1);

}

char* newStr(int size) { //Create a new string

    char * tmp = malloc(sizeof(char)*size);

    memset(tmp, 0x00, sizeof(char)*size); //Clear the new memory

    return tmp;

}

char* rszStr(char *str, int size) { //Resize a string

    str = realloc(str, sizeof(char)*size);

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
        if(isspace(str[i]) || str[i] == FILLER_STRING_CHAR || str[i] == '\n' || str[i] == '\t' || str[i] == '\0' || str[i] == '\a' || str[i] == '\b' || str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
            whiSpc++;

    return whiSpc == strlen(str);

}

int isCharSpcl(char chr){

    return (!isalpha(chr) && chr != '0' && chr != '1' && chr != '2' && chr != '3' && chr != '4' && chr != '5' && chr != '6' && chr != '7' && chr != '8' && chr != '9');

}

int isKnwnSpclChr(char chr){

    return (chr == '%' || chr == '?' || chr == '/' || chr == '>' || chr == '<' || chr == '.' || chr == ',' || chr == '|' || chr == '\\' || chr == '"' || chr == '\'' || chr == ':' || chr == ';' || chr == '}' || chr == '{' || chr == ']' || chr == '[' || chr == '=' || chr == '-' || chr == '+' || chr == '_' || chr == '(' || chr == ')' || chr == '*' || chr == '&' || chr == '^' || chr == '$' || chr == '#' || chr == '@' || chr == '!' || chr == '`' || chr == '~');

}