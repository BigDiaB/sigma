
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"


int main(__attribute__((unused))int argc, __attribute__((unused))char* argv[])
{
    unsigned int i, len;
    char* str, *code;

    str = "TEST";
    code = malloc((len = strlen(str)) + 1);

    memset(code,0,len +1);

    enigma_init(1,2,3,0,5,0);

    for (i = 0; i < len; i++)
    {
        printf("%c",code[i] = enigma(str[i],0));
    }
    puts("");


    enigma_init(1,2,3,0,5,0);

    for (i = 0; i < len; i++)
    {
        printf("%c",enigma(code[i],0));
    }
    puts("");

    free(code);

    exit(0);
}
