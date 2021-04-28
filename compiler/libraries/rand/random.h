#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../types/string/extr.h"

static int mRan(int minVal, int maxVal){
    int ran = rand() % (int)(maxVal + 1);
    while(ran < minVal || ran > maxVal) //This is a bad idea
        ran = rand() % (int)(maxVal + 1);
    return ran;
}

static char* randStr(size_t size, char *mode) {

    char *str = malloc(sizeof(char)*size), *chrSet;

    if(getChrIndx(mode, 'N') != -1){
        chrSet = apdStr(chrSet, "0123456789");
    }

    if(getChrIndx(mode, 'S') != -1)
        chrSet = apdStr(chrSet, "abcdefghijklmnopqrstuvwxyz");

    if(getChrIndx(mode, 'C') != -1)
        chrSet = apdStr(chrSet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    if (size) {
        for (size_t n = 0; n < size; n++) {
            int key = mRan(0, sizeof(chrSet));
            str[n] = chrSet[key];
        }
        str[size - 1] = '\0';
    }

    return str;
}