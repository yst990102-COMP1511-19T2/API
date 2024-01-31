// Modified 3/3/2017 by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

// Test if a year is leap year
// https://en.wikipedia.org/wiki/Leap_year

#include <stdio.h>

int main(void) {
    int year;

    printf("Enter year: ");
    if (scanf("%d", &year) != 1) {
        return 1;
    }

    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }

    return 0;
}
