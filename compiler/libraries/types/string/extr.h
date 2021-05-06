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

char* getStrPrt(char *str, int strIndx, int endIndx) { //Resize a string
    /*if(strIndx == endIndx){
        //Throw an error!
    }else */if(endIndx > strlen(str) || endIndx < strIndx){
        //Throw an error!
    }else if(strIndx > strlen(str) || strIndx < 0){
        //Throw an error!
    }else{
        char *nStr = malloc((endIndx - strIndx + 2)*sizeof(char));
        for(int i = 0; strIndx <= endIndx; strIndx++, i++){
            nStr[i] = str[strIndx];
            if(endIndx == strIndx)
                nStr[++i] = '\0';
        }
        str = nStr;
    }

    return str;

}