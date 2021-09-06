#include <stdio.h>
#include <stdlib.h>
#include "../rand/random.h"

static TmpFileStruc genFilStr(char *pth){ //Create a new file in the `/tmp` directory

    char *str, *oth;

    if(OUTPUT_TEMP_FILE){

        oth = pth;
 
        str = apdStr(pth, OUTPUT_INPUT_COLLECTION_FILE_EXTENSION);

    }else{

        char *rnd = randStr(10, "NSC");

        str = apdStr("tmp/", rnd);

        free(rnd);

        strcpy(oth, str);

        str = apdStr(str, OUTPUT_INPUT_COLLECTION_FILE_EXTENSION);

    }

    TmpFileStruc tmp = {fopen(str, "w"), oth};

    free(str);

    return tmp;

}