typedef struct {
    FILE *ptr;
    FILE *strPtr;
    char *pth;
    int maxId;
} datCtr;

datCtr tmpDatCtr;

void crtDatFil(){

    tmpDatCtr.pth = malloc(sizeof(char)*(strlen(wrkstn.Path) + strlen(wrkstn.Name) + 6));

    sprintf(tmpDatCtr.pth, "%s%c%s.dat", wrkstn.Path, PATH_SLASH_TYP_CHAR, wrkstn.Name);

    tmpDatCtr.ptr = fopen(tmpDatCtr.pth, "w"); //Create a new data file in "write mode"
    fclose(tmpDatCtr.ptr);
    tmpDatCtr.ptr = fopen(tmpDatCtr.pth, "a+"); //Create a new data file in "write mode"

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

char *getDat(char typ, int id, int goBck){

    char *lin = malloc(sizeof(char)*(MAX_LINE_LENGTH + 1));

    unsigned int aftMthPos = (goBck) ? ftell(tmpDatCtr.ptr) : 0;

    fseek(tmpDatCtr.ptr, 0, SEEK_SET); //Go to the start of the file!

    fgets(lin, MAX_LINE_LENGTH, tmpDatCtr.ptr);

    if(lin[strlen(lin) - 1] == '\n')
        lin[strlen(lin) - 1] = '\0';

    char *dat = NULL;
    int fnd = 0, wait = 1, keepLoop = 1;

    do{

        if(lin[0] == typ){

            char *tmp = getStrPrt(lin, 2, 8, 0);
            int tmpId = hexToInt(tmp);

            if(tmpId == id){

                fnd = 1;
                dat = getStrPrt(lin, 9, strlen(lin), 0);

            }

        }

        if(!fnd && keepLoop){

            fgets(lin, MAX_LINE_LENGTH, tmpDatCtr.ptr);

            if(lin[strlen(lin) - 1] == '\n')
                lin[strlen(lin) - 1] = '\0';

            if(wait)
                keepLoop = !feof(tmpDatCtr.ptr);

            if(!wait)
                keepLoop = 0;

            if(!keepLoop && wait){
                keepLoop = 1;
                wait = 0;
            }

        }

    }while(!fnd && keepLoop);

    /*if(!fnd && feof(tmpDatCtr.ptr)){

        dat = malloc(sizeof(char)*(strlen(ERROR_FIL_ENDOFFILE) + 1));
        strcpy(dat, ERROR_FIL_ENDOFFILE);

    }*/
    if(!fnd){

        dat = malloc(sizeof(char)*1);
        dat[0] = '\0';

    }

    fseek(tmpDatCtr.ptr, aftMthPos, SEEK_END); //Go to the end of the file
    free(lin);

    return dat;

}

char* getDatByNam(char typ, char *valNam, int goBck){

    int idx = 1, brk = 0;
    char *dat = getDat(typ, idx, goBck);
    char *val = malloc(sizeof(char)*(1));
    val[0] = '\0';

    //printf("\n%s", getDat('C', 6, 1));

    while(!brk && idx <= tmpDatCtr.maxId){

        if(dat[0] != '\0'){

            //printf("\n{\n    `%s`,", dat);

            int spcIndx = getStrIndx(dat, " ");

            char *tmpNamStr = getStrPrt(dat, 0, spcIndx, 0);

            //printf("\n    `%s`\n},", tmpNamStr);

            //printf("\n[%s,%s]", tmpNamStr, valNam);

            if(strcmp(tmpNamStr, valNam) == 0){

                printf("\nYAY!");

                free(val);
                val = getStrPrt(dat, spcIndx + 1, strlen(dat), 0);

                brk = 1;

            }

            free(tmpNamStr);

        }

        idx++;

        if(!brk && idx <= tmpDatCtr.maxId){

            free(dat);

            dat = getDat(typ, idx, goBck);
            //printf("\n[%d, %c, '%s']", idx, typ, dat);

        }

    }

    free(dat);

    return val;

}

void clsDatFil(){

    fprintf(tmpDatCtr.ptr, "#");
    fclose(tmpDatCtr.ptr);
    tmpDatCtr.ptr = NULL;

}