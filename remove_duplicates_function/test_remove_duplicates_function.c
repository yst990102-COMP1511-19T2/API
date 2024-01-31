#include <stdio.h>
#include <stdlib.h>

int remove_duplicates(int size, int source[size], int dest[]);
void print_array(int size, int array[size]);

#undef main
int main(int argc, char *argv[]) {
    int length = argc - 1;
    int source[length];
    int dest[length];
    for (int i = 0; i < length; i++)
        dest[i] = -1;
    for (int i = 1; i < argc; i++)
        source[i - 1] = atoi(argv[i]);
    int retval = remove_duplicates(length, source, dest);
    if (retval)
        print_array(retval, dest);
    printf("return value: %d\n", retval);
    return 0;
}

void print_array(int size, int array[size]) {
    for (int i=0; i<size; i++) {
        // If you're getting an error here, that means you have uninitialised values
        // in the array you returned from your remove_duplicates function.
        printf("%d ", array[i]);
    }
    printf("\n");
}
