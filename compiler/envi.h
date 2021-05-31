//You will find all the environment variables here.




//Files

#define MAX_LINE_LENGTH 509 //The maximum line length in files
#define MAX_PATH_LENGTH 255 //The maximum path length
#define MAX_FILE_NAME_LENGTH 150 //The maximum file name length


//Strings

#define MAX_LONG_STRING_LENGTH 536870900 //The maximum long string length
#define MAX_NORMAL_STRING_LENGTH 5368709 //The maximum normal string length
#define MAX_SHORT_STRING_LENGTH 309 //The maximum short string length
#define FILLER_STRING_CHAR '0' //The character used to generate a filler string


//Paths

#define PATH_SLASH "\\"


//Output (NOTE: some of these files might still get generated in the `/tmp` directory)

#define OUTPUT_LOG_FILE 1 //Output a `.log` file (Logs files may affect the speed of
//the compiler severely. The log file stream is constantly closed and re-opened to
//ensure that the user will get the logs even when the compiler crashes.)
#define OUTPUT_TEMP_FILE 1 //Output a `.tesf` file (stage one code)
/* (!) Still not implemented */ #define OUTPUT_C_CODE_FILE 0 //Output a `.c` file (stage two code)
/* (!) Still not implemented */ #define OUTPUT_EXECUTABLE 1 //Output an executable file (stage three code)


//Process End Management

/* (!) Still not implemented */ #define EMPTY_COMPILER_TMP_DIR //Empty the `/compiler/tmp/` directory at the end of every process