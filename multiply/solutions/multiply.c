// A program that prints the absolute multiplication between two integers
// Written 15/06/2019
// by Tom Kunc (t.kunc@unsw.edu.au)
// for COMP1511

#include <stdio.h>

int main(void) {
    int x, y;

    scanf("%d", &x);
    scanf("%d", &y);

    if (x * y == 0) {
        printf("zero\n");
    } else if (x * y > 0) {
        printf("%d\n", x * y);
    } else {
        printf("%d\n", x * y * -1);
    }

    return 0;
}
