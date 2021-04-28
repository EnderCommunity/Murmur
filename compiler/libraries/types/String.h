#include <stdio.h>

typedef struct {
    int maxLen;
    int len;
    char typ;
    char **con;
} _Str;

static _Str* defStr(char type){
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

static void setStrVal(_Str *tmp, char *value){
    tmp->len = strlen(value);
    if(tmp->len <= tmp->maxLen){
        realloc(tmp, sizeof(_Str) + (tmp->len-1)*sizeof(char));
        tmp->con = (char **)malloc(tmp->len*sizeof(char));
        tmp->con = (char **)value;
    }else
        0; //Throw an error!!!!!!!
    //printf("%d", tmp->len);
    //Deb();
    /*for((tmp->len) = 0; (tmp->len) < (tmp->maxLen); (tmp->len)++){
        printf("Loop \"%d\", Max Length \"%d\", value %c", (tmp->len), (tmp->maxLen), value[(tmp->len)]);
        Deb();
        realloc(tmp, sizeof(_Str) + ((tmp->len))*sizeof(char));
        Deb();
        realloc(tmp->con, sizeof(char)*((tmp->len) + 1));
        //realloc((tmp->con), (tmp->len + 1)*sizeof(char));
        //strcpy(tmp[(tmp->len)], value[(tmp->len)]);
        //(tmp->con)[(tmp->len)] = value[(tmp->len)];
        Deb();
        (tmp->con)[(tmp->len)] = value[(tmp->len)];
        Deb();
        //if(value[(tmp->len)] == NULL)
        //    break;
    }*/
    //Deb();
}

static char** getStrVal(_Str *tmp){
    return tmp->con;
}

static void merStrVal(_Str *tmp, char *str){ //FAILS
    Deb();
    tmp->len += strlen(str);
    Deb();
    if(tmp->len <= tmp->maxLen){
        Deb();
        realloc(tmp, sizeof(_Str) + (tmp->len-1)*sizeof(char));
        Deb();
        realloc(tmp->con, tmp->len*sizeof(char));
        Deb();
        //*tmp->con = ("%s%s", *tmp->con, str);
        strcat(*tmp->con, str);
    }else
        0; //Throw an error!!!!
}