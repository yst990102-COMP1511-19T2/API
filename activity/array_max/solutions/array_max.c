// Find the maximum value in an array.
// Sample solution.

#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 1000

int array_max(int size, int array[size]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    int array[MAX_SIZE];

    // Get the array size.
    int size;
    printf("Enter array size: ");
    scanf("%d", &size);
    assert(size > 0);

    // Scan in values for the array.
    printf("Enter array values: ");
    int i = 0;
    while (i < size) {
        assert(scanf("%d", &array[i]) == 1);
        i = i + 1;
    }

    printf("Maximum value is %d.\n", array_max(size, array));

    return 0;
}

// Return the largest value in a given array.
int array_max(int size, int array[size]) {
    // Set the max to initially be the first element in the array.
    int max = array[0];
    int i = 0;
    while (i < size) {
        // If we find something that's bigger than our current max...
        if (array[i] > max) {
            // ... update our current max to that value.
            max = array[i];
        }
        i = i + 1;
    }

    return max;
}
