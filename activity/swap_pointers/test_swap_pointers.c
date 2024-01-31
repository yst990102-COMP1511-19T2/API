#include <stdio.h>
#include <stdlib.h>

void swap_pointers(int *a, int *b);

#undef main

int main(int argc, char *argv[]) {
    int first = strtol(argv[1], NULL, 10);
    int second = strtol(argv[2], NULL, 10);
    
    swap_pointers(&first, &second);
    printf("%d %d\n", first, second);

    return 0;
}
