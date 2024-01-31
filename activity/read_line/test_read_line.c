#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#undef main
void read_line(int, char []);

int main(int argc, char *argv[]) {
    assert(argc > 1);
    char buffer[atoi(argv[1])];

    read_line(sizeof buffer, buffer);

    // if you an error here, you haven't null-terminated buffer
    printf("<%s>\n", buffer);
    return 0;
}
