char *incPrsFilPth;
char *prsFilPth;
FILE *prsFilPtr = NULL;

void crtPrsFil(int typ){ //Create a parser file

    incPrsFilPth = apdStr(wrkstn.Path, wrkstn.Name);
    prsFilPth = apdStr(incPrsFilPth, (typ) ? ".trm" : ".prs");

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
    free(incPrsFilPth);
    fclose(prsFilPtr);

}
