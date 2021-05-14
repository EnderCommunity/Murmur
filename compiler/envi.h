//You will find all the environment variables here.

//Files
#define MAX_LINE_LENGTH 509 //The maximum line length in files
#define MAX_PATH_LENGTH 255 //The maximum path length

//Strings
#define MAX_LONG_STRING_LENGTH 536870900 //The maximum long string length
#define MAX_NORMAL_STRING_LENGTH 5368709 //The maximum normal string length
#define MAX_SHORT_STRING_LENGTH 309 //The maximum short string length

//Output (NOTE: all these files are still gonna be generated in the `/tmp` directory,
//these settings give you the option to get a copy of these files in the directory of
//the file you compiled)
#define OUTPUT_TEMP_FILE 0 //Output a `.tesf` file (stage one code)
#define OUTPUT_C_CODE_FILE 0 //Output a `.c` file (stage two code)
#define OUTPUT_EXECUTABLE 1 //Output an executable file (stage three code)