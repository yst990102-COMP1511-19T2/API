#include <stdio.h>
#include <stdlib.h>

int count_bigger(int length, int array[]);

#undef main

int main(int argc, char *argv[]) {
    int length = argc - 1;
    int array[length];
    for (int i = 1; i < argc; i++)
        array[i - 1] = atoi(argv[i]);

    // If you're getting an error here,
    // you have returned an uninitialized value
    printf("%d\n", count_bigger(length, array));
    return 0;
}
