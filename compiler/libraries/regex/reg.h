#include <regex.h>

int regChk(char *exp, char *str){ //Do a regex check

    //Source: https://stackoverflow.com/questions/1085083/regular-expressions-in-c-examples

    regex_t regex;

    int reti;
    char msgbuf[100];


    reti = regcomp(&regex, exp, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, str, 0, NULL, 0);

    if (!reti) {

        regfree(&regex);

        return 1;

    } else if (reti == REG_NOMATCH) {

        regfree(&regex);

        return 0;

    } else {

        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        exit(1);
        return -1;

    }

}