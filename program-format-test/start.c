#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    int OS = 0;

    // 1: win32, 2: win64, 3: Linux, 4: macOS, 5: Android, 6: iPhone, 7: Unix-based

    #if _WIN64
        OS = 2; //win-64

    #elif _WIN32
        OS = 1; //win-32

    #elif __ANDROID__
        OS = 5; //Android

    #elif TARGET_OS_MAC
        OS = 4; //MacOS

    #elif TARGET_OS_IPHONE
        OS = 6; //iPhone

    #elif TARGET_OS_EMBEDDED
        OS = 6; //iOS-embedded

    #elif TARGET_IPHONE_SIMULATOR
        OS = 6; //iOS-simulator

    #elif __linux__
        OS = 3; //Linux

    #elif __unix__
        OS = 7; //Unix-based

    #endif

    char slsh;

    if(OS == 1 || OS == 2) { //Windows

        slsh = '\\';

    }else if(OS == 3 || OS == 4 || OS == 7) { //Linux, macOS, and unix-based

        slsh = '/';

    }else{ //Other operating systems

        return -100; //Unsupported environment

    }

    char cmd[13];

    sprintf(cmd, "core%cbin%crun", slsh, slsh);

    return system(cmd); //Start the program!

}