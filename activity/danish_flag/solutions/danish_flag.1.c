// Danish Flag -- sample solution.
// Draws a Danish Flag.
// NOTE: this version uses functions, which have not been covered yet

#include <stdio.h>
#include <stdlib.h>

void printFlag(int size);
void printRows(int size);
void printRow(int size);
void printMiddleRows(int size);
void printMiddleRow(int size);


// Our main function is as simple as it can be:
//   1. get the input
//   2. print the flag
// All of the complexity has been moved to other functions.

int main(int argc, char *argv[]) {
    int size;
    printf("Enter the flag size: ");
    scanf("%d", &size);

    printFlag(size);

    return 0;
}


// Printing the flag involves the following steps:
// 1. Print the top rows
// 2. Print the middle rows
// 3. Print the bottom rows.
//
// So, our printFlag function does exactly this. The function is clear
// and readable, and there's no complex logic -- it just prints the
// flag, as described.
void printFlag(int size) {
    printRows(size);

    printMiddleRows(size);

    printRows(size);
}

// Print the rows -- we need 2*size-1 rows at the top and bottom.
void printRows(int size) {
    int i = 0;
    while (i < 2 * size - 1) {
        printRow(size);
        i = i + 1;
    }
}

// Print out one row.
void printRow(int size) {
    int i = 0;
    while (i < size - 1) {
        printf("###");
        i = i + 1;
    }

    printf("##  ##");

    i = 0;
    while (i < 2 * size - 1) {
        printf("###");
        i = i + 1;
    }

    printf("\n");
}

// Print out the middle rows -- there are two of them.
void printMiddleRows(int size) {
    printMiddleRow(size);
    printMiddleRow(size);

}

void printMiddleRow(int size) {
    int i = 0;
    while (i < size * 3) {
        printf("   ");
        i = i + 1;
    }
    printf("\n");
}
