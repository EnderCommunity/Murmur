#include <stdio.h>
#include "process.h"
#include "../libraries/files/extra.h"

struct ProcessInfo SetMode(struct FileContent fileData){

    struct ProcessInfo CurrentProcess = {0};

    int *fRows = files_SplitLines(fileData.content);

    //Incomplete!

    return CurrentProcess;

}

//printf("%d", CurrentProcess.firstPostOnly);