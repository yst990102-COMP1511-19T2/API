#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int array_max(int size, int array[size]);
static void print_array(int size, int array[size]);

#undef main
int main(int argc, char *argv[]) {
    int length = argc - 1;
    if (length < 1) {
        return 0;
    }
    int array[length];

    for (int i = 1; i < argc; i++) {
        array[i - 1] = atoi(argv[i]);
    }

    int maximum = array_max(length, array);

    print_array(length, array);

    // If you're getting an error here,
    // you have returned an uninitialized value
    printf("Maximum value: %d\n", maximum);

    return 0;
}


static void print_array(int size, int array[size]) {
    printf("Array: [");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i != size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
