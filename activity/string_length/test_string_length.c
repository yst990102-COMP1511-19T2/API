#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#undef main
int string_length(char []);

int main(int argc, char *argv[]) {
    assert(argc > 1);
    printf("%d\n", string_length(argv[1]));
    return 0;
}
