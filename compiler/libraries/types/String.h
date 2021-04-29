#include <stdio.h>

typedef struct { //A string structure

    int maxLen;
    int len;
    char typ;
    char **con;

} _Str;

static _Str* defStr(char type){ //Define a string

    _Str *tmp = malloc(sizeof(_Str));

    tmp->con = (char **)malloc(sizeof(char));
    tmp->typ = type;

    if(type == 'L')
        tmp->maxLen = 536870900;
    else if(type == 'N')
        tmp->maxLen = 5368709;
    else if(type == 'S')
        tmp->maxLen = 309;
    else
        tmp->maxLen = type;

    return tmp;

}

static void setStrVal(_Str *tmp, char *value){ //Set a string's value

    tmp->len = strlen(value);

    if(tmp->len <= tmp->maxLen){

        realloc(tmp, sizeof(_Str) + (tmp->len-1)*sizeof(char));
        tmp->con = (char **)malloc(tmp->len*sizeof(char));
        tmp->con = (char **)value;

    }else
        0; //Throw an error!!!!!!!

}

static char** getStrVal(_Str *tmp){ //Get a string's value

    return tmp->con;

}