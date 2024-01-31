// Copy an array.
// A sample solution.

#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 1000

void scan_array(int size, int array[size]);
void show_array(int size, int array[size]);
void copy_array(int size, int from_array[size], int to_array[size]);

// DO NOT CHANGE THIS MAIN FUNCITON
int main(int argc, char *argv[]) {

    // Create the arrays.
    int array1[MAX_SIZE];
    int array2[MAX_SIZE];

    // Get the array size.
    int size;
    printf("Enter array size: ");
    assert(scanf("%d", &size) == 1);
    assert(size > 0);

    // Scan in the values for the array.
    printf("Enter array values: ");
    scan_array(size, array1);

    // Print the values of the first array.
    show_array(size, array1);

    // Copy the values from array1 to array2.
    copy_array(size, array1, array2);

    // Print the copied values.
    show_array(size, array2);

    return 0;
}

// Copy `size` elements from `from_array` into `to_array`.
void copy_array(int size, int from_array[size], int to_array[size]) {
    int i = 0;
    while (i < size) {
        to_array[i] = from_array[i];
        i = i + 1;
    }
}


// This function reads in values from standard input into an array.
// It assumes scanf successfully reads in a number.
void scan_array(int size, int array[size]) {
    int i = 0;
    while (i < size) {
        int items_read = scanf("%d", &array[i]);
        assert(items_read == 1);
        i = i + 1;
    }
}

// This function prints the array in the format
// [1, 2, 3, ...]
void show_array(int size, int array[size]) {
    // Print open bracket
    printf("[");

    // If the array has elements, print them
    if (size > 0) {
        // Print the first element separately
        printf("%d", array[0]);

        // Loop over the rest of the elements
        int i = 1;
        while (i < size) {

            // Print in list format
            printf(", %d", array[i]);
            i = i + 1;
        }
    }

    // Print closing bracket
    printf("]\n");
}
