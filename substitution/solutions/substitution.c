//  Written 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  Write stdin to stdout encrypted with a Substitution cipher
//  https://en.wikipedia.org/wiki/Substitution_cipher
//
//  The mapping will be supplied as a command-line argument containing 26 characters:
//  These will be an an ordering of the letters 'a'..'z'.

#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE  26

int encrypt(int character, char mapping[ALPHABET_SIZE]);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <mapping>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[1]) != ALPHABET_SIZE) {
        printf("%s: mapping must contain %d letters\n", argv[0], ALPHABET_SIZE);
        return 1;
    }

    int character = getchar();
    while (character != EOF) {
        int encrypted_character = encrypt(character, argv[1]);
        putchar(encrypted_character);
        character = getchar();
    }

    return 0;
}

// encrypt letters with a substitution cipher with the specified mapping

int encrypt(int character, char mapping[ALPHABET_SIZE]) {
    if (character >= 'A' && character <= 'Z') {
        return mapping[character - 'A'] - 'a' + 'A';
    } else if (character >= 'a' && character <= 'z') {
        return mapping[character - 'a'];
    } else {
        return character;
    }
}
