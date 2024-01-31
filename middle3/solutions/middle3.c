// Modified 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)

// Print middle of 3 integers

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

    // a, b, c can be in any order

    // swap a & b if they are not in order
    if (a > b) {
        tmp = b;
        b = a;
        a = tmp;
    }

    // swap a & c if they are not in order
    if (a > c) {
        tmp = c;
        c = a;
        a = tmp;
    }

    // a must be the smallest now

    // swap b & c if they are not in order
    if (b > c) {
        tmp = c;
        c = b;
        b = tmp;
    }

    // a, b, c now in  order

    printf("Middle: %d\n", b);

    return 0;
}
