#include <stdio.h>
#include <stdlib.h>
#include "libraries/rand/random.h"

static FILE* genFilStr(){ //Used to create a new file

    char *rnd = randStr(10, "NSC");

    char *str = apdStr("tmp/", rnd);

    str = apdStr(str, ".tesf");

    printf("%s\n", str);

    FILE *tmpPtr = fopen(str, "w");

    return tmpPtr;
    //return (FILE *)fopen(apdStr("/tmp/", randStr(10, "NSC")), "w");

}