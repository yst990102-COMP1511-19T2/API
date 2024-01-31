#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#undef main
int strings_equal(char *, char *);

int main(int argc, char *argv[]) {
    assert(argc > 2);
    printf("%d\n", strings_equal(argv[1], argv[2]));
    return 0;
}
