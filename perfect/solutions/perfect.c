// Test if a number is perfect
// Written 26/3/2017
// by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

#include <stdio.h>

int main(void) {
    int number, sum, i;

    printf("Enter number: ");

    scanf("%d", &number);

    printf("The factors of %d are:\n", number);

    i = 1;
    sum = 0;
    while (i <= number) {
        if ((number % i) == 0 ) {
            printf("%d\n", i);
            sum = sum + i;
        }
        i = i + 1;
    }

    printf("Sum of factors = %d\n", sum);

    if (number == (sum - number)) {
        printf("%d is a perfect number\n", number);
    } else {
        printf("%d is not a perfect number\n", number);
    }

    return 0;
}
