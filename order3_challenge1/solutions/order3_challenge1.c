// Modified 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

// Print 3 integers in non-decreasing order
// without using functions: if/while or other control statements, ?:
// using only  C covered in the first 2 weeks of COMP1511 lectures

// This is a puzzle not a programming exercises

#include <stdio.h>

int main(void) {
    int a, b, c;
    int tmp;

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

    tmp = b;
    b = a - (1 - (a > b)) * (a - b);
    a = a - (1 - (a < tmp)) * (a - tmp);
    tmp = c;
    c = a - (1 - (a > c)) * (a - c);
    a = a - (1 - (a < tmp)) * (a - tmp);
    tmp = c;
    c = b - (1 - (b > c)) * (b - c);
    b = b - (1 - (b < tmp)) * (b - tmp);

    printf("The integers in order are: %d %d %d\n", a, b, c);

    return 0;
}
