// Print out characters in lower case.

#include <stdio.h>

int lowercase(int c);

int main(int argc, char *argv[]) {

    // Scan in the character.
    int c = getchar();

    // Loop until there are no more characters to scan.
    while (c != EOF) {
        // Print the character, in lowercase.
        putchar(lowercase(c));

        // Get the next character.
        c = getchar();
    }

    return 0;
}

// The difference between lowercase and uppercase letters.
// If we had the letter 'A', and we added _something_ to it, we would
// get 'a' -- as the ascii values for lowercase letters are higher than
// the ascii values for uppercase letters.
//
// The _something_ that we have to add is the difference between lower
// and uppercase letters.
// e.g. 'A' + ('a' - 'A') can be rearranged to 'A' - 'A' + 'a',
// which gives us lowercase 'a'.

int lowercase(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}
