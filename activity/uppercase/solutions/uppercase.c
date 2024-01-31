// alex linker 2017-08-17
// main function for uppercase activity

#include <stdio.h>

int uppercase(int c);

int main(int argc, char *argv[]) {

    // get the character
    int c = getchar();

    // loop until end of characters
    while (c != EOF) {
        // print the character in uppercase
        putchar(uppercase(c));

        //get the next character
        c = getchar();
    }

    return 0;
}

int uppercase(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    } else {
        return c;
    }
}
