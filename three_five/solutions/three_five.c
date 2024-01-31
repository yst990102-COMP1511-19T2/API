// Written 16/3/2018
// by Andrew Taylor (andrewt@cse.unsw.edu.au)
// as a lab example for COMP1511
// Suggested by a https://projecteuler.net/ problem

// Print multiples of 3 or 5 < n

#include <stdio.h>

int main(void) {
    int number, i;

    printf("Enter number: ");
    scanf("%d", &number);

    i = 1;
    while (i < number) {
        if (i % 3 == 0 || i % 5 == 0) {
            printf("%d\n", i);
        }
        i = i + 1;
    }

    return 0;
}
