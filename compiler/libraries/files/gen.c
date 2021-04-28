#include <stdio.h>
#include <stdlib.h>
#include "../rand/random.h"

static FILE* genFilStr(){ //Create a new file in the `/tmp` directory

    char *rnd = randStr(10, "NSC"), *str;

    str = apdStr("tmp/", rnd);

    str = apdStr(str, ".tesf");

    printf("%s\n", str);

    FILE *tmpPtr = fopen(str, "w");

    return tmpPtr;
    //return (FILE *)fopen(apdStr("/tmp/", randStr(10, "NSC")), "w");

}