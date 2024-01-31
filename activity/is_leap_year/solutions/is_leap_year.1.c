// Modified by Finbar Berkon (finbar.berkon@unsw.edu.au)
// from https://en.wikipedia.org/wiki/Leap_year#Algorithm
// on 16/6/2019

// Test if a year is a leap year with a simple series of if statements

#include <stdio.h>

int main(void) {
    int year;

    printf("Enter year: ");
    if (scanf("%d", &year) != 1) {
        return 1;
    }

    if (year % 4 != 0) {
        printf("%d is not a leap year.\n", year);
    } else if (year % 100 != 0) {
        printf("%d is a leap year.\n", year); 
    } else if (year % 400 != 0) {
        printf("%d is not a leap year.\n", year);
    } else {
        printf("%d is a leap year.\n", year); 
    }
}
