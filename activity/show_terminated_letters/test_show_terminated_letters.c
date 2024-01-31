#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#undef main
int show_terminated_letters(char *);

int main(int argc, char *argv[]) {
    assert(argc > 1);
    show_terminated_letters(argv[1]);
    return 0;
}
