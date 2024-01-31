// A program to check if 3 numbers are strictly increasing, decreasing or neither.
// Written 15/06/2019
// by Tom Kunc (t.kunc@unsw.edu.au)
// for COMP1511

#include <stdio.h>

int main(void) {
    double a, b, c;
    printf("Please enter three numbers: ");
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);

    if (a < b && b < c) {
        printf("up\n");
    } else if (a > b && b > c) {
        printf("down\n");
    } else {
        printf("neither\n");
    }
    return 0;
}
