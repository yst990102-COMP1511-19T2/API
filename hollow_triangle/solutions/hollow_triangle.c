// Written 14/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
// as a test for COMP1511

// Print a hollow triangle

#include <stdio.h>

int main(void) {

    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    int row = 1;
    while (row <= size) {
        int col = 1;
        while (col <= row) {
            // row == size gives horizontal line
            // row == col gives diagonal line
            // col == 1 gives vertical line
            if (row == size || col == 1 || row == col) {
                printf("*");
            } else {
                printf(" ");
            }
            col = col + 1;
        }
        printf("\n");
        row = row + 1;
    }

    return 0;
}
