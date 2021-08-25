FILE *prsFnlFilPtr = NULL;

void crtFnlPrsFil(char *pth){ //Create a `.prs` file!

    char *tmpPth = apdStr(pth, ".prs");

    prsFnlFilPtr = fopen(tmpPth, "w");

    free(tmpPth);

    if(prsFnlFilPtr == NULL){

        exit(-100);

    }

}

void clsFnlPrsFil(){ //Close the `.prs` file!

    fclose(prsFnlFilPtr);

}

void isrtPrsNTrm(char *nam, char *cnt, int srcLin){ //Insert a terminal value

    fprintf(prsFnlFilPtr, "%s(%s)<%d>\n", nam, cnt, srcLin);

}

void isrtPrsMltNTrm(char *nam, char *cnt, int srcLin){ //Insert a terminal value

    fprintf(prsFnlFilPtr, "%s(%s)<%d>:\n", nam, cnt, srcLin);

}

void isrtPrsEndNTrm(){ //Insert a terminal value

    fprintf(prsFnlFilPtr, ";\n");

}