char *prsFilPth;
FILE *prsFilPtr = NULL;

void crtPrsFil(char *rotPth){ //Create a parser file

    prsFilPth = apdStr(rotPth, ".trm");

    prsFilPtr = fopen(prsFilPth, "w");

    if(prsFilPtr == NULL){

        exit(-100);

    }

}

void isrtPrsTrm(char *typ, char *val, int linId){ //Insert a terminal value

    fprintf(prsFilPtr, "%s(%s)<%d>\n", typ, val, linId);

}

void clsPrsFil(){ //Close the parser file

    free(prsFilPth);
    fclose(prsFilPtr);

}
