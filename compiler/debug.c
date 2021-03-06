#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Leave me a alone...

double timSpt = 0.0;
clock_t timBeg, timEnd;

void RegDebStr(){ //Start the timer

    timBeg = clock();

}

void RegDebEnd(){ //Stop the timer

    timEnd = clock();

    timSpt += (double)(timEnd - timBeg) / CLOCKS_PER_SEC;
 
    printf("[Compiler] The elapsed time is %f seconds\n", timSpt);

}

void Debug(char msg[], int pause){ //A simple debug message

    if(DEBUG_OUTPUT_TO_CONSOLE){

        printf("[Debug] %s\n", msg);

        if(pause)
            SYSTEM_COMMANDS_PAUSE;

    }

}

void DebugWithPath(char msg[], char path[], int pause){ //A debug message with a path within the message itself

    if(DEBUG_OUTPUT_TO_CONSOLE){

        printf("[Debug] %s%s\n", msg, path);

        if(pause)
            SYSTEM_COMMANDS_PAUSE;

    }

}