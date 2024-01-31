// Modified 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

// Print 3 integers in non-decreasing order
// without using: functions, if/while or other control statements, ?:
// using only  C covered in the first 2 weeks of COMP1511 lectures
// and only using 3 int variables

// This is a puzzle not a programming exercises

#include <stdio.h>

int main(void) {
    int a, b, c;

    printf("Enter integer: ");
    if (scanf("%d", &a) != 1) {
        return 1; // EXIT_FAILURE would be more portable
    }

    printf("Enter integer: ");
    if (scanf("%d", &b) != 1) {
        return 1;
    }

    printf("Enter integer: ");
    if (scanf("%d", &c) != 1) {
        return 1;
    }

    printf("The integers in order are:");
    printf(" %d", a - (1 - (a < (b - (1 - (b < c)) * (b - c)))) * (a - (b - (1 - (b < c)) * (b - c))));
    printf(" %d", (a - (1 - (a < b)) * (a - b)) - (1 - ((a - (1 - (a < b)) * (a - b)) > (c - (1 - (c < (a - (1 - (a > b)) * (a - b)))) * (c - (a - (1 - (a > b)) * (a - b)))))) * ((a - (1 - (a < b)) * (a - b)) - (c - (1 - (c < (a - (1 - (a > b)) * (a - b)))) * (c - (a - (1 - (a > b)) * (a - b))))));
    printf(" %d", a - (1 - (a > (b - (1 - (b > c)) * (b - c)))) * (a - (b - (1 - (b > c)) * (b - c))));
    printf("\n");

    return 0;
}
