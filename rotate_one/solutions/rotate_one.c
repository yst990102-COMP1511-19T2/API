// Rotate a character by one -- i.e. turn 'a' to 'b', 'b' to 'c', ...
// 'z' to 'a'.
// A sample solution.

#include <stdio.h>

char rotateOne(char c);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {

    // Scan in the first character.
    int c = getchar();

    // Loop until there are no more characters to scan.
    while (c != EOF) {
        // Print the character, "rotated" once.
        putchar(rotateOne(c));

        // Get the next character.
        c = getchar();
    }

    return 0;
}
// END OF MAIN FUNCTION

// "Rotate" the letter by one, i.e. change 'a' to 'b', 'b' to 'c',
// ..., 'z' to 'a'.
char rotateOne(char c) {
    // If the character is between 'a' and 'y', we can just add one
    // to it.
    if ((c >= 'a' && c <= 'y') || (c >= 'A' && c <= 'Y')) {
        c = c + 1;
    } else if (c == 'z') {
        // If it's 'z', we can't just add one -- we need it to wrap
        // around.
        c = 'a';
    } else if (c == 'Z') {
        // Similarly for capital 'Z'.
        c = 'A';
    }

    return c;
}
