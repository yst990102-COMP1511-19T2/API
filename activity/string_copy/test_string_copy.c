#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#undef main
int string_copy(char *, char *, int);

int main(int argc, char *argv[]) {
    assert(argc > 2);
    char buffer[atoi(argv[2])];
    string_copy(buffer, argv[1], sizeof buffer);

    // if you get an error error you have not null-terminated the buffer
    printf("<%s>\n", buffer);
    return 0;
}
