FILE* lexProc(FileInfo *fileInf, TmpFileStruc cFileObj){

    FILE *lexFil = fopen(apdStr(cFileObj.pth, ".lxic"), "w");

    fclose(lexFil);
    lexFil = fopen(apdStr(cFileObj.pth, ".lxic"), "r");

    return lexFil;

}