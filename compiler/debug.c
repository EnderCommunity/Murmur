#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

//Leave me a alone...

double timSpt = 0.0;
clock_t timBeg, timEnd;

void RegDebStr(){ //Start the timer
    timBeg = clock();
}

void RegDebEnd(){ //Stop the timer
    timEnd = clock();

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    timSpt += (double)(timEnd - timBeg) / CLOCKS_PER_SEC;
 
    printf("\n\n[Debug] The elapsed time is %f seconds\n", timSpt);
}

void Debug(char msg[], int pause){ //A simple debug message
    printf("[Debug] %s\n", msg);
    if(pause)
        system("pause");
}

void DebugWithPath(char msg[], char path[], int pause){ //A debug message with a path within the message itself
    /*printf("Debug!");
    system("pause");
    _Str *tmp = defStr('S');
    printf("Debug!");
    system("pause");
    setStrVal(tmp, msg);
    printf("Debug!");
    system("pause");
    merStrVal(tmp, path);
    printf("Debug!");
    system("pause");*/
    printf("[Debug] %s%s\n", msg, path);
    if(pause)
        system("pause");
    /*printf("Debug!");
    /*for(int i = 0; *(path+i) != NULL; i++){ //Nope, this ain't working
        //Stop working on everyhting, and define the variable types first to make this
        //Process much easier to deal with.
        strcat(temp, (char *)(path + i));
    }
    Debug(temp, pause);*/
    //Debug(msg, pause);
}