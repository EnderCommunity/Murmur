#include <math.h>

int hexToInt(char *hex){

    int dec = 0, base = 1;
    int i = 0, value, length;
    length = strlen(hex);

    for(i = length--; i >= 0; i--){

        if(hex[i] >= '0' && hex[i] <= '9'){

            dec += (hex[i] - 48) * base;
            base *= 16;

        }else if(hex[i] >= 'A' && hex[i] <= 'F'){

            dec += (hex[i] - 55) * base;
            base *= 16;

        }else if(hex[i] >= 'a' && hex[i] <= 'f'){

            dec += (hex[i] - 87) * base;
            base *= 16;

        }

    }

    return dec;
}

char *intToHex(int dec){

    int dec, quotient;
	int i=1,j,temp;
	char *hex;
	quotient = dec;

	while(quotient!=0) {

		temp = quotient % 16;

		if( temp < 10)
		           temp =temp + 48; else
		         temp = temp + 55;

		hex[i++]= temp;
		quotient = quotient / 16;

	}

    hex[i + 1] = '\0';

	return hex;

}