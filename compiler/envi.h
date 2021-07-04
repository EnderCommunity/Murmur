//You will find all the environment variables here.



//Files

#define MAX_LINE_LENGTH 509 //The maximum line length in files
#define MAX_PATH_LENGTH 255 //The maximum path length
#define MAX_FILE_NAME_LENGTH 150 //The maximum file name length


//Strings

/* (!) Still not implemented */ #define MAX_LONG_STRING_LENGTH 819208 //The maximum long string length
/* (!) Still not implemented */ #define MAX_NORMAL_STRING_LENGTH 2048 //The maximum normal string length
/* (!) Still not implemented */ #define MAX_SHORT_STRING_LENGTH 256 //The maximum short string length
#define FILLER_STRING_CHAR '\t' //The character used to generate a filler string
#define FILLER_STRING_CHAR_TYP_STR "\t" //The character used to generate a filler string (in a string type)


//Paths

#define PATH_SLASH "\\"
#define PATH_SLASH_TYP_CHAR '\\'


//Output (NOTE: some of these files might still get generated in the `/tmp` directory)

#define OUTPUT_LOG_FILE 1 //Output a `.log` file (Logs files may affect the speed of
//the compiler severely. The log file stream is constantly closed and re-opened to
//ensure that the user will get the logs even when the compiler crashes.)
#define OUTPUT_TEMP_FILE 1 //Output a `.tmp` file (stage one code)
/* (!) Still not implemented */ #define OUTPUT_C_CODE_FILE 0 //Output a `.c` file (stage two code)
#define OUTPUT_EXECUTABLE 1 //Output an executable file (stage three code)



//Preprocessor

#define ENABLE_PREPROCESSOR_METHODS 1 //Enable preprocessor methods (will not effect the header method)
#define ENABLE_PREPROCESSOR_HEADER 1 //Enable the `##header` method
#define ENABLE_PREPROCESSOR_SKIP_FLAG 1 //Enable the head `--skip` preprocessor flag


//Comments

#define ENABLE_COMMENTS 1 //Enable comments detection an filtering
#define SUPPORT_LINEAR_COMMENTS 1 //The compiler will identify and remove linear comments from your code when this option is enabled
#define SUPPORT_MULTI_LINEAR_COMMENTS 1 //The compiler will identify and remove multi-linear comments from your code when this option is enabled


//Lexer

#define LEXER_SYMBOL 1001
#define LEXER_SYMBOL_STR "1001"
#define LEXER_STRING 1002
#define LEXER_STRING_STR "1002"
#define LEXER_CHAR 1003
#define LEXER_CHAR_STR "1003"
#define LEXER_NUMBER 1004
#define LEXER_NUMBER_STR "1004"
#define LEXER_OPERATOR 1005
#define LEXER_OPERATOR_STR "1005"


//States

/* (!) Still not implemented */ #define ENABLE_STATES 1 //Functions, groups, and classes will be forced to have a state definition (If disabled, all states will be set to 'public' with no way to change that)


//Compiler Process Termination

/* (!) Still not implemented */ #define EMPTY_COMPILER_TMP_DIR 0 //Empty the `/compiler/tmp/` directory at the end of every process
#define C_COMPILER_EXECUTABLE_DIR "C:\\msys64\\mingw64\\bin\\gcc.exe" //The directory of your C compiler of choice
