//  Written 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  Write stdin to stdout with upper case letters converted to lower case
// and lower case converted to upper case
//
//  The shift will be supplied as a command-line argument

#include <stdio.h>
#include <stdlib.h>

int swap_case(int character);

int main(int argc, char *argv[]) {
    int character = getchar();
    while (character != EOF) {
        int swapped_character = swap_case(character);
        putchar(swapped_character);
        character = getchar();
    }

    return 0;
}


int swap_case(int character) {
    if (character >= 'A' && character <= 'Z') {
        return 'a' + character - 'A';
    } else if (character >= 'a' && character <= 'z') {
        return 'A' + character - 'a';
    } else {
        return character;
    }
}
