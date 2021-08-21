typedef struct {
    char *src;
    int lin;
    int col;
} Inf_Token;

Inf_Token getLxrInfTkn(int srcLin){

    Inf_Token tmp;

    // Temp (change this later)
    tmp.src = malloc(sizeof(char)*(strlen("UNKNOWN") + 1));
    strcpy(tmp.src, "UNKNOWN");
    tmp.lin = -1;
    tmp.col = -1;

    return tmp;

}

void delLxrInfTkn(Inf_Token tmp){

    free(tmp.src);

}