#include <stdio.h>
#include "process.h"

FileInfo* checkFlags(FILE *filePtr, char *path, int isFull, char* srcPth){

    FileInfo *tmp;
    tmp = defFileDatObj(filePtr, path, isFull, srcPth);

    return tmp;

}