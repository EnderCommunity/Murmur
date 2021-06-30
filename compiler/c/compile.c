/*void cmplCCode(char *path){

    char *cmd = apdStr(
        apdStr(apdStr("start \"", C_COMPILER_EXECUTABLE_DIR), "\""),
        apdStr(" \"", apdStr(path, "\"")));

    char *tmp = apdStr(apdStr("Executing the command: `", cmd), "`");

    writeLogLine("Compiler Manager", 0, tmp, 0, 0, 0);
    int Return = (int) system(cmd);


    if (Return <= 32){

        printf("Cannot open file. File may have been moved or deleted.");


    }

}*/

#include <windows.h>
#include <ShellApi.h>

void cmplCCode(char *path){
    ShellExecute(NULL, "open", C_COMPILER_EXECUTABLE_DIR, apdStr(path, apdStr(" -o ", wrkstn.Name)), wrkstn.Path, SW_SHOW);
}


//ShellExecute(NULL, NULL, "cmd.exe", "/k cd /d d:\your\path", NULL, SW_SHOW);