#include <regex.h>
//#include "regex.h"
//#include "../../../outer/regex-2.7-bin/include/regex.h"
//#include "C:/Users/adels/Desktop/EnderCommunity/Projects/Murmur/outer/regex-2.7-bin/include/regex.h"

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

    /* Execute regular expression */
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {

        puts("Match");

    } else if (reti == REG_NOMATCH) {

        puts("No match");

    } else {

        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);

    }

    /* Free memory allocated to the pattern buffer by regcomp() */
    regfree(&regex);

}
