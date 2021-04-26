#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Debug(char *msg, int pause){
    printf("[Debug] %s\n", msg);
    if(pause)
        system("pause");
}

void DebugWithPath(char *msg, char *path, int pause){
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