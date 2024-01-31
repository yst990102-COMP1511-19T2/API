// Read characters until eof
// Andrew Taylor - andrewt@unsw.edu.au
// 22/4/2018

#include <stdio.h>

int main(void) {
    // getchar returns an int which will contain either
    // the ASCII code of the character (if input is ASCII) or EOF

    int ch = getchar();
    while (ch != EOF) {
        putchar(ch);
        ch = getchar();
    }
    return 0;
}
