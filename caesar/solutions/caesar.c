//  Written 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  Write stdin to stdout encrypted with a Caesar Cipher
//  https://en.wikipedia.org/wiki/Caesar_cipher
//
//  The shift will be supplied as a command-line argument

#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE  26

int encrypt(int character, int shift);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <shift>\n", argv[0]);
        return 1;
    }

    int shift = atoi(argv[1]);

    // negative shifts need to be converted to the equivalent positive shift
    if (shift < 0) {
        shift = ALPHABET_SIZE + (shift % ALPHABET_SIZE);
    }

    int character = getchar();
    while (character != EOF) {
        int encrypted_character = encrypt(character, shift);
        putchar(encrypted_character);
        character = getchar();
    }

    return 0;
}

// encrypt letters with a caesar cipher with the specified shift
// the specified characters is returned shifted the specified number of positions
// characters other than letters are returned unchanged

int encrypt(int character, int shift) {
    if (character >= 'A' && character <= 'Z') {
        return 'A' + (character - 'A' + shift) % ALPHABET_SIZE;
    } else if (character >= 'a' && character <= 'z') {
        return 'a' + (character - 'a' + shift) % ALPHABET_SIZE;
    } else {
        return character;
    }
}
