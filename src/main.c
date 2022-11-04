
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"

#define MAX_STR_LEN 256

int main(__attribute__((unused))int argc, __attribute__((unused))char* argv[])
{
    unsigned int i, len, debug;
    char str[MAX_STR_LEN], *code;

    int rotors[3];
    int offsets[3];

    debug = 0;

    printf("Rotoren: ");
    scanf("%d %d %d", &rotors[0],&rotors[1],&rotors[2]);

    printf("Stellungen: ");
    scanf("%d %d %d", &offsets[0],&offsets[1],&offsets[2]);

    printf("Text: ");
    scanf("%s", str);

    code = malloc((len = strlen(str)) + 1);
    memset(code,0,len +1);

    enigma_init(rotors[0],rotors[1],rotors[2],offsets[0],offsets[1],offsets[2]);

    for (i = 0; i < len; i++)
        printf("%c%c",code[i] = enigma(str[i],debug), i == len -1 || debug ? 10 : 0);

    printf("Rotoren: ");
    scanf("%d %d %d", &rotors[0],&rotors[1],&rotors[2]);

    printf("Stellungen: ");
    scanf("%d %d %d", &offsets[0],&offsets[1],&offsets[2]);

    enigma_init(rotors[0],rotors[1],rotors[2],offsets[0],offsets[1],offsets[2]);

    for (i = 0; i < len; i++)
        printf("%c%c",enigma(code[i],debug), i == len -1 || debug  ? 10 : 0);

    free(code);

    exit(0);

}
