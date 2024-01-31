#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#undef main
int show_letters(int, char *);

int main(int argc, char *argv[]) {
    assert(argc > 1);
    show_letters(atoi(argv[2]), argv[1]);
    return 0;
}
