#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../types/string/extr.h"

int mRan(int minVal, int maxVal){ //Generate a random number
    int ran = rand() % (int)(maxVal + 1);
    while(ran < minVal || ran > maxVal) //This is a bad idea
        ran = rand() % (int)(maxVal + 1);
    //printf("\n1: %d\n2: %d\n", ran, rand() % (maxVal - minVal) + minVal);
    return ran;
    //return rand() % (maxVal - minVal) + minVal;
}

char* randStr(int size, char *mode) { //Generate a random string

    char *str = newStr(size + 1), *chrSet = newStr(62);

    if(getChrIndx(mode, 'N') != -1)
        chrSet = apdStr(chrSet, "0123456789");

    if(getChrIndx(mode, 'S') != -1)
        chrSet = apdStr(chrSet, "abcdefghijklmnopqrstuvwxyz");

    if(getChrIndx(mode, 'C') != -1)
        chrSet = apdStr(chrSet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    if (size) {
        for (int n = 0; n < size; n++) {
            int ran = mRan(0, sizeof(chrSet)/sizeof(char));
            str[n] = chrSet[ran];
        }
        str[size] = '\0';
    }

    return str;
}