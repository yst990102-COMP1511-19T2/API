// Print out the written form of a given number between 1 and 5.
// A sample solution.

#include <stdio.h>

int main(void) {
    int num;

    // Read in the number.
    printf("Please enter an integer: ");
    scanf("%d", &num);

    // Start by printing "You entered ", since all of the variations
    // start with that.
    printf("You entered ");

    // Print out the appropriate number or message.
    if (num < 1) {
        printf("a number less than one");
    } else if (num == 1) {
        printf("one");
    } else if (num == 2) {
        printf("two");
    } else if (num == 3) {
        printf("three");
    } else if (num == 4) {
        printf("four");
    } else if (num == 5) {
        printf("five");
    } else {
        printf("a number greater than five");
    }

    // Print the full stop at the end.
    printf(".\n");

    return 0;
}
