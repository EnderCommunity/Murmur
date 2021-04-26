typedef struct{
    int length;
    int *cLength;
    char *type;
    union content{
        char cha;
        char *str;
        int intg;
        int intg;
    };
} Array;

typedef struct{
    int length;
    int dimensions;
} MDArray;