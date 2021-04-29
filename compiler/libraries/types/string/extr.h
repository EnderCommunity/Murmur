int getChrIndx(char *str, char chr){ //Get the index of a char in a string
    int indx = (int)((char *)strchr(str, chr) - str);
    return indx >= 0 ? indx : -1;
}

int getStrIndx(char *str, char *strForChk){ //Get the index of a string in a string (weird behaviour has been noticed)
    //return (int)((char *)strchr(str, chr) - str);
    //int substringLength = strlen(str) - position;
    /*char *result = strstr(str, strForChk);
    int position = result - str;
    int substringLength = strlen(str) - position;
    printf("\n1st String: %s\n2nd String: %s\n1: %d\n2: %d\n", str, strForChk, strlen(str), position);
    return substringLength;*/
    //return ((char *)strstr(str, strForChk) - str);
    int indx = (char *)strstr(str, strForChk) - str;
    return indx >= 0 ? indx : -1;
}

int inStrRng(char *str, char *strForChk){ //Check if a string exists inside a string
    return strstr(str, strForChk) != NULL;
}

char* apdStr(char *dest, char *str){ //Append two stings
    char* rslt = calloc(strlen(dest) + strlen(str), sizeof(char));
    strcpy(rslt, dest);
    strcat(rslt, str);
    //rslt[sizeof(rslt)/sizeof(char)] = '\0';
    return rslt;
}

char* newStr(int size) { //Create a new string
    char * tmp = malloc(sizeof(char)*size);
    tmp[0] = '\0';
    return tmp;
}

char* rszStr(char *str, int size) { //Create a new string
    str = realloc(str, sizeof(char)*size);
    return str;
}