static int getChrIndx(char *str, char chr){ //WORKING
    return (int)((char *)strchr(str, chr) - str);
}

char* apdStr(char *dest, char *str){
    char* rslt = malloc(sizeof(char)*(strlen(dest) + strlen(str)));
    strcpy(rslt, dest);
    strcat(rslt, str);
    return rslt;
}