#include <stdio.h>
#include "process.h"
//#include "../libraries/files/extra.h"
//#include "../types/FileContent.h"

FileInfo* checkFlags(FILE *filePtr, char *path, int isFull){
    FileInfo *tmp;
    tmp = defFileDatObj(filePtr, path, isFull);
    return tmp;
}