// Print out an ASCII table of "character numbers".

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 32;
    while (i < 127) {
        printf("%3d 0x%x %c\n", i, i, i);
        i = i + 1;
    }
    return 0;
}
