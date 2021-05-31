#include <stdio.h>
#include "process.h"
//#include "../libraries/files/extra.h"
//#include "../types/FileContent.h"

FileInfo* checkFlags(FILE *filePtr, char *path, int isFull){

    FileInfo *tmp;
    tmp = defFileDatObj(filePtr, path, isFull);

    writeLogLine("Preprocessor", 0, "The header flags have been processed successfully!", 0, 0, 0);

    return tmp;

}