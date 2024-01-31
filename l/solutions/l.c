// Written 14/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
// as a test  for COMP1511

// Print a capital L

#include <stdio.h>

int main(void) {
    int size = 0;
    printf("Enter size: ");
    scanf("%d", &size);

    int row = 0;
    while (row < size - 1) {
        printf("*\n");
        row = row + 1;
    }

    int column = 0;
    while (column < size) {
        printf("*");
        column = column + 1;
    }
    printf("\n");

    return 0;
}
