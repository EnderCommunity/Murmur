#include <stdio.h>
#include "process.h"

FileInfo* checkFlags(FILE *filePtr, char *path, int isFull){

    FileInfo *tmp;
    tmp = defFileDatObj(filePtr, path, isFull);

    return tmp;

}