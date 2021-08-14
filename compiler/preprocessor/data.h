typedef struct {
    FILE *ptr;
    char *pth;
    int maxId;
} datCtr;

datCtr tmpDatCtr;

void crtDatFil(){

    tmpDatCtr.pth = malloc(sizeof(char)*(strlen(wrkstn.Path) + strlen(wrkstn.Name) + 6));

    sprintf(tmpDatCtr.pth, "%s%c%s.dat", wrkstn.Path, PATH_SLASH_TYP_CHAR, wrkstn.Name);

    tmpDatCtr.ptr = fopen(tmpDatCtr.pth, "w"); //Create a new data file in "write mode"

    tmpDatCtr.maxId = 0;

}

void freeDatFil(){

    free(tmpDatCtr.pth);

}

int savDat(char typ, char *dat){

    (tmpDatCtr.maxId)++;

    fprintf(tmpDatCtr.ptr, "%cx%06X %s\n", typ, tmpDatCtr.maxId, dat);

    return tmpDatCtr.maxId;

}

void clsDatFil(){

    fprintf(tmpDatCtr.ptr, "#");
    fclose(tmpDatCtr.ptr);
    tmpDatCtr.ptr = NULL;

}

/*
000000      100          
^ Data ID   ^ Data type  ^ The data
*/