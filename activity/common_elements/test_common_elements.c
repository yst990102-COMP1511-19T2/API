// argv[0]
// argv[1] = length
// argv[2] = 0th value of array1
// argv[3] = 1st value of array1
// argv[length+1] = last value of array1
// argv[length+2] = 0th value of array2
// argv[length+3] = 1st value of array2
// argv[length+length+1] = last value of array2
// ?????

#include <stdio.h>
#include <stdlib.h>

int common_elements(int length, int source1[length], int source2[length], int destination[length]);
void print_array(int size, int array[size]);
void fill_array(int size, int array[size], int value);

#undef main
// input format:
// length, $length values for array1, $length values for array2
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    if (argc % 2 == 0) {
        fprintf(stderr, "%s: warning odd number of arguments\n", argv[0]);
    }
    int length = argc/2;
    int array1[length];
    int array2[length];
    int dest[length];
    // fill the dest array with -1s to make it easier to debug errors
    fill_array(length, dest, -1);

    for (int i = 0; i < length; i++) {
        array1[i] = atoi(argv[1 + i]);
        array2[i] = atoi(argv[length + 1 + i]);
    }

    int retval = common_elements(length, array1, array2, dest);
    if (retval)
        print_array(retval, dest);
    printf("return value: %d\n", retval);
    return 0;
}

void print_array(int size, int array[size]) {

    for (int i=0; i<size; i++) {
        // If you're getting an error here, that means you have uninitialised values
        // in the array you returned from your common_elements function.
        printf("%d ", array[i]);
    }
    printf("\n");
}

void fill_array(int size, int array[size], int value) {
    for (int i=0; i<size; i++) {
        array[i] = value;
    }
}
