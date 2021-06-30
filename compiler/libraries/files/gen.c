#include <stdio.h>
#include <stdlib.h>
#include "../rand/random.h"

static TmpFileStruc genFilStr(char *pth){ //Create a new file in the `/tmp` directory

    //char *str = malloc(MAX_PATH_LENGTH*sizeof(char));
    char *str, *oth;

    if(OUTPUT_TEMP_FILE){

        //strcpy(oth, pth);
        oth = pth;
 
        str = apdStr(pth, ".tmp");

    }else{

        char *rnd = randStr(10, "NSC");

        str = apdStr("tmp/", rnd);

        strcpy(oth, str);

        str = apdStr(str, ".tmp");

    }

    printf("%s\n", str);

    TmpFileStruc tmp = {fopen(str, "w"), oth};

    //free(str);

    return tmp;

}