#include <stdio.h>
#include <stdlib.h>

#undef numbers

struct numbers {
    int first;
    int second;
};

struct numbers *struct_create(int a, int b);

#undef main

int main(int argc, char *argv[]) {
    int first = strtol(argv[1], NULL, 10);
    int second = strtol(argv[2], NULL, 10);
    
    struct numbers* n = struct_create(first, second);
    printf("%d %d\n", n->first, n->second);

    return 0;
}
