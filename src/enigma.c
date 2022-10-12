
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uchar;
#include "enigma.h"

uchar settings[6][26] = {
/* Input 		"ABCDEFGHIJKLMNOPQRSTUVWXYZ" */
/* 1: */ 		"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
/* 2: */ 		"AJDKSIRUXBLHWTMCQGZNPYFVOE",
/* 3: */ 		"BDFHJLCPRTXVZNYEIWGAKMUSQO",
/* 4: */ 		"ESOVPZJAYQUIRHXLNFTGKDCMWB",
/* 5: */ 		"VZBRGITYUPSDNHLXAWMJQOFECK",
/*Reflector:*/ 	"YRUHQSLDPXNGOKMIEBFZCWVJAT"
};

uchar plugs[10][2];
uchar plugs_used = 0;

uchar rotors[3] = {1,2,3};
uchar rotor_offsets[3] = {0, 0, 0};

void enigma_init(uchar r1, uchar r2, uchar r3, uchar o1, uchar o2, uchar o3)
{
	rotors[0] = r1;
	rotors[1] = r2;
	rotors[2] = r3;

	rotor_offsets[0] = o1;
	rotor_offsets[1] = o2;
	rotor_offsets[2] = o3;
}

void set_plug(char A, char B)
{
	plugs_used++;
    plugs[plugs_used -1][0] = A;
    plugs[plugs_used -1][1] = B;

}

static uchar cti(uchar c)
{
    return c - 65;
}

static uchar itc(uchar i)
{
    return i + 65;
}

static uchar rotateb(uchar input, uchar rotor)
{
    uchar ret = input;

    uchar i = 0;
    while(i < 26)
    {
    	uchar c = i + rotor_offsets[rotor -1];
	    if (c >= 26)
	        c -= 26;
        if (cti(settings[rotors[rotor -1] -1][c]) == ret)
        {
            return i;
        }
        i++;
    }


    puts("Ya dungoofed");
    exit(EXIT_FAILURE);
}

static uchar rotatef(uchar input, uchar rotor)
{
    uchar ret = input + rotor_offsets[rotor -1];

    if (ret >= 26)
        ret -= 26;

    ret = cti(settings[rotors[rotor -1] -1][ret]);
    return ret;
}

static uchar rotatec(uchar input)
{
    uchar ret = input;

    ret = cti(settings[5][ret]);
    return ret;
}

static void increment_rotor_offset()
{
    rotor_offsets[0]++;
    if (rotor_offsets[0]  >= 26)
    {
        rotor_offsets[0] = 0;
        rotor_offsets[1]++;
        if (rotor_offsets[1]  >= 26)
        {
            rotor_offsets[1] = 0;
            rotor_offsets[2]++;
            if (rotor_offsets[2]  >= 26)
                rotor_offsets[2] = 0;
        }
    }
}

static uchar check_plugs(uchar input)
{
    uchar i, c = itc(input);
    for (i = 0; i < 10; i++)
    {
        if (plugs[i][0] == c)
            return cti(plugs[i][1]);

        if (plugs[i][1] == c)
            return cti(plugs[i][0]);
    }
    return input;
}

void clear_plugs()
{
	plugs_used = 0;
}

void pop_plug()
{
	plugs_used--;
}

uchar enigma(uchar input, uchar print)
{

	if (input < 65 || input > 90)
		return 0;

	input = cti(input);

    if (print)
    	printf("Input:\t\t %c (%d)\n",itc(input),input);

    input = check_plugs(input);
    if (print)
    	printf("Plugboard:\t %c (%d)\n",itc(input),input);

    input = rotatef(input, 1);
    if (print)
    	printf("Rotor 1F:\t %c (%d)\n",itc(input), input);

    input = rotatef(input, 2);
    if (print)
    	printf("Rotor 2F:\t %c (%d)\n",itc(input), input);

    input = rotatef(input, 3);
    if (print)
    	printf("Rotor 3F:\t %c (%d)\n",itc(input), input);

    input = rotatec(input);
    if (print)
    	printf("Reflector:\t\t %c (%d)\n",itc(input), input);

    input = rotateb(input, 3);
    if (print)
    	printf("Rotor 3B:\t %c (%d)\n",itc(input), input);

    input = rotateb(input, 2);
    if (print)
    	printf("Rotor 2B:\t %c (%d)\n",itc(input), input);

    input = rotateb(input, 1);
    if (print)
    	printf("Rotor 1B:\t %c (%d)\n",itc(input), input);

    input = check_plugs(input);
    if (print)
    	printf("Plugboard:\t %c (%d)\n",itc(input),input);

    if (print)
    	printf("Offsets:\t %d %d %d\n",rotor_offsets[0],rotor_offsets[1],rotor_offsets[2]);

    if (print)
    	printf("Output:\t\t %c (%d)\n\n",itc(input),input);

    increment_rotor_offset();

    return itc(input);
}