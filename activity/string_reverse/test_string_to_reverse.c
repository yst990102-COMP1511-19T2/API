#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#undef main
void string_reverse(char []);

int main(int argc, char *argv[]) {
    assert(argc > 1);
    char buffer[strlen(argv[1]) + 1];
    strcpy(buffer, argv[1]);

    // if you get an error you have removed the null-terminator from the buffer
    string_reverse(buffer);
    printf("%s\n", buffer);
    return 0;
}
