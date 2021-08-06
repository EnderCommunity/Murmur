char* chrToStr(char chr){

    char *str = malloc(2*sizeof(char));

    str[0] = chr;
    str[1] = '\0';

    return str;

}

int isSyb(char chr){

    char *tmpChr = chrToStr(chr);

    int rslt = (regChk("[_a-zA-Z]", tmpChr) && (!isCharSpcl(chr) || chr == '_'));

    free(tmpChr);

    return rslt;
}

int isSybE(char chr){

    char *tmpChr = chrToStr(chr);

    int rslt = (regChk("[_a-zA-Z0-9]", tmpChr) && (!isCharSpcl(chr) || chr == '_'));

    free(tmpChr);

    return rslt;

}

int isThrMor(char chr){

    char *tmpChr = chrToStr(chr);

    int rslt = ((isSyb(chr) || regChk("[0-9]", tmpChr)) && !isspace(chr));

    free(tmpChr);

    return rslt;

}