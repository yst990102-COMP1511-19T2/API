//  Written 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  read characters from stdin and write to stdout
//  except lower case vowels ('a', 'e','i', 'o', 'u') are not written

#include <stdio.h>

int is_vowel(int character);

int main(void) {
    // getchar returns an int which will contain either
    // the ASCII code of the character read or EOF

    int character = getchar();
    while (character != EOF) {

        if (!is_vowel(character)) {
            putchar(character);
        }

        character = getchar();
    }

    return 0;
}

// return 1 if character is a lower case vowel
// 0 otherwise

int is_vowel(int character) {
    return character == 'a' ||
           character == 'e' ||
           character == 'i' ||
           character == 'o' ||
           character == 'u';
}
