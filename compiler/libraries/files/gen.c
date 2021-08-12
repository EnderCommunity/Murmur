#include <stdio.h>
#include <stdlib.h>
#include "../rand/random.h"

static TmpFileStruc genFilStr(char *pth){ //Create a new file in the `/tmp` directory

    char *str, *oth;

    if(OUTPUT_TEMP_FILE){

        oth = pth;
 
        str = apdStr(pth, ".tmp");

    }else{

        char *rnd = randStr(10, "NSC");

        str = apdStr("tmp/", rnd);

        free(rnd);

        strcpy(oth, str);

        str = apdStr(str, ".tmp");

    }

    printf("%s\n", str);

    TmpFileStruc tmp = {fopen(str, "w"), oth};

    free(str);

    return tmp;

}