// Read in a number, and determine whether it is negative.
// If the number is positive, print "You have entered a positive number"
// If the number is a zero, print "You have entered zero".
// If the number is negative, print "Don't be so negative!"
// Sample solution.

#include <stdio.h>

int main(void) {
    int num;

    // Read in a number.
    scanf("%d", &num);

    // Print the relevant message.
    if (num > 0) {
        printf("You have entered a positive number.\n");
    } else if (num == 0) {
        printf("You have entered zero.\n");
    } else {
        printf("Don't be so negative!\n");
    }

    return 0;
}
