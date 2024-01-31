// Print out an array.
// A sample solution.

#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 1000

void show_array(int size, int array[size]);

// DO NOT CHANGE THIS MAIN FUNCITON
int main(int argc, char *argv[]) {
    // Create the array.
    int array[MAX_SIZE];

    // Get the array size.
    int size;
    printf("Enter array size: ");
    assert(scanf("%d", &size) == 1);
    assert(size > 0);

    // Scan in values for the array.
    printf("Enter array values: ");
    int i = 0;
    while (i < size) {
        assert(scanf("%d", &array[i]) == 1);
        i = i + 1;
    }

    // Print the values.
    show_array(size, array);

    return 0;
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
