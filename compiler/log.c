typedef struct {
    FILE *filePtr;
    char *path;
} LogFile;

LogFile globalLogFile;

void newLogFile(char *path){

    if(OUTPUT_LOG_FILE){

        globalLogFile.path = malloc((strlen(path) + 1)*sizeof(char));
        strcpy(globalLogFile.path, path);
        globalLogFile.filePtr = fopen(globalLogFile.path, "w");

        fprintf(globalLogFile.filePtr, "[?][LOG SYSTEM] => Created a log file successfully!\n[!][Compiler Manager] => The workstation directory has been set to \"%s\"\n", wrkstn.Path);

        fclose(globalLogFile.filePtr);

    }

}

void clsLogSec(){ //Free all of the variables

    free(globalLogFile.path);

}

void writeLogLine(char *title, int type, char *message, int lines, int line, int col){ //Write into the log file (type 0 - "info", type 1 - "warning", other type values - "error")

    if(OUTPUT_LOG_FILE){

        globalLogFile.filePtr = fopen(globalLogFile.path, "a");

        if(lines)
            fprintf(globalLogFile.filePtr, "[%c][%s][%d, %d] => %s\n", (type == 0) ? '?' : ((type == 1) ? '!' : 'X'), title, line, col, message);
        else
            fprintf(globalLogFile.filePtr, "[%c][%s] => %s\n", (type == 0) ? '?' : ((type == 1) ? '!' : 'X'), title, message);

        fclose(globalLogFile.filePtr);
    }

}