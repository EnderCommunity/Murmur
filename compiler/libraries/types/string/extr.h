static int getChrIndx(char *str, char chr){ //Get the index of a char in a string
    return (int)((char *)strchr(str, chr) - str);
}

char* apdStr(char *dest, char *str){ //Append two stings
    char* rslt = malloc(sizeof(char)*(strlen(dest) + strlen(str)));
    strcpy(rslt, dest);
    strcat(rslt, str);
    return rslt;
}