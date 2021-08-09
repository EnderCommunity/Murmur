#if _WIN64 || _WIN32

    #include <windows.h>
    #include <ShellApi.h>

    void cmplCCode(char *path){ //Compile a C file

        ShellExecute(NULL, "open", C_COMPILER_EXECUTABLE_DIR, apdStr(path, apdStr(" -o ", wrkstn.Name)), wrkstn.Path, SW_SHOW);

    }

#else

    void cmplCCode(char *path){ //Compile a C file (not windows)

        //???

    }

#endif
