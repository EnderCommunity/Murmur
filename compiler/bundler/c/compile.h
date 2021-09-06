/*#if _WIN64 || _WIN32

    #include <windows.h>
    #include <ShellApi.h>

    void cmplCCode(char *path){ //Compile a C file

        ShellExecute(NULL, "open", C_COMPILER_EXECUTABLE_DIR, apdStr(path, apdStr(" -o ", wrkstn.Name)), wrkstn.Path, SW_SHOW);

    }

#else

    void cmplCCode(char *path){ //Compile a C file (not windows)

        //???

    }

#endif*/

void cmpCCode(char *path){ //Compile a C file

    char *cmd = malloc(sizeof(char)*(
                      strlen(C_COMPILER_EXECUTABLE_DIR)
                      + strlen(path)
                      + strlen(wrkstn.Path)
                      + strlen(wrkstn.Name)
                      + strlen(OUTPUT_EXECUTABLE_EXT)
                      + 5
                      + 1 //'\0'
                      ));

    sprintf(cmd, "%s %s -o %s%s%s",
                    C_COMPILER_EXECUTABLE_DIR,
                    path,
                    wrkstn.Path,
                    wrkstn.Name,
                    OUTPUT_EXECUTABLE_EXT);

    system(cmd);

    free(cmd);

}

//gcc <INPUT> -o <OUTPUT>

// -Os <I>
//      Optimise for size
// -fdata-sections -ffunction-sections <IO> -Wl,--gc-sections
//      Remove un-used functions
// -Wall -save-temps <I>
//      Get all intermediate files