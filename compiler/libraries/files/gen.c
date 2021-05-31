#include <stdio.h>
#include <stdlib.h>
#include "../rand/random.h"

static FILE* genFilStr(char *pth){ //Create a new file in the `/tmp` directory

    char *str;

    if(OUTPUT_TEMP_FILE)
        str = apdStr(pth, ".tesf");
    else{

        char *rnd = randStr(10, "NSC");

        str = apdStr("tmp/", rnd);

        str = apdStr(str, ".tesf");

    }

    printf("%s\n", str);

    FILE *tmpPtr = fopen(str, "w");

    return tmpPtr;

}