//  Written 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  Write stdin to stdout decrypted with a Substitution cipher
//  https://en.wikipedia.org/wiki/Substitution_cipher
//
// The mapping used to encrypt the input
// will be supplied as a command-line argument containing 26 characters:
// These will be an an ordering of the letters 'a'..'z'.

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ALPHABET_SIZE 26

void compute_inverse_mapping(char mapping[ALPHABET_SIZE], char inverse_mapping[ALPHABET_SIZE]);
int decrypt(int character, char  inverse_mapping[ALPHABET_SIZE]);

int main(int argc, char *argv[]) {
    char inverse_mapping[ALPHABET_SIZE] = {0};

    if (argc != 2) {
        printf("Usage: %s <mapping>\n", argv[0]);
        return 1;
    }
    if (strlen(argv[1]) != ALPHABET_SIZE) {
        printf("%s: mapping must contain %d letters\n", argv[0], ALPHABET_SIZE);
        return 1;
    }

    compute_inverse_mapping(argv[1], inverse_mapping);

    int character = getchar();
    while (character != EOF) {
        int decrypted_character = decrypt(character, inverse_mapping);
        putchar(decrypted_character);
        character = getchar();
    }

    return 0;
}


// mapping must contain an ordering of letters 'a'..'z'
// the inverse_mapping will be stored in inverse_mapping

void compute_inverse_mapping(char mapping[ALPHABET_SIZE], char inverse_mapping[ALPHABET_SIZE]) {
    int i = 0;
    while (i < ALPHABET_SIZE) {
        int character = mapping[i];
        assert(character >= 'a' && character <= 'z');
        inverse_mapping[character - 'a'] = 'a' + i;
        i = i + 1;
    }
}

// decrypt letters with a substitution cipher with the specified inverse_mapping

int decrypt(int character, char inverse_mapping[ALPHABET_SIZE]) {
    if (character >= 'A' && character <= 'Z') {
        return inverse_mapping[character - 'A'] - 'a' + 'A';
    } else if (character >= 'a' && character <= 'z') {
        return inverse_mapping[character - 'a'];
    } else {
        return character;
    }
}
