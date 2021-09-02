void insTllDat(char *dat, int lin, int col){

    char *tmpStr = malloc(sizeof(char)*(
        strlen(dat) +
        10 +
        18 +
        1
    ));

    sprintf(tmpStr, "%s <Zx%09X> <Zx%09X>", dat, lin, col);

    savDat(TELL_VALUE, tmpStr);

    free(tmpStr);

}
