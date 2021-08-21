typedef struct {
    FILE *ptr;
    FILE *strPtr;
    char *pth;
} tllFil;

tllFil tmpTllFil;

void crtTllFil(){

    tmpTllFil.pth = malloc(sizeof(char)*(strlen(wrkstn.Path) + strlen(wrkstn.Name) + 6));

    sprintf(tmpTllFil.pth, "%s%c%s.tll", wrkstn.Path, PATH_SLASH_TYP_CHAR, wrkstn.Name);

    tmpTllFil.ptr = fopen(tmpTllFil.pth, "w"); //Create a new data file in "write mode"
    //fclose(tmpTllFil.ptr);
    //tmpTllFil.ptr = fopen(tmpTllFil.pth, "a+"); //Create a new data file in "write mode"

}

void freeTllFil(){

    free(tmpTllFil.pth);

}

void insTllDat(char *dat){

    fprintf(tmpTllFil.ptr, "%s\n", dat);

}

void clsTllFil(){

    fprintf(tmpTllFil.ptr, "::end::");
    fclose(tmpTllFil.ptr);
    tmpTllFil.ptr = NULL;

}