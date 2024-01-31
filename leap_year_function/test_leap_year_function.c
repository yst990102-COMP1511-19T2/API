#include <stdio.h>

int isLeapYear(int year);

#undef main

int main(void) {

    // Scan in the year.
    int year;
    printf("Enter year: ");

    if (scanf("%d", &year) != 1) {
        return 1;
    }

    // We've moved all of the logic that was here into a function.
    if (isLeapYear(year) == 1) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }

    return 0;
}
