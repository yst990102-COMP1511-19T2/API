// Word Addition -- a sample solution.
// Add two numbers and print them out, as words.

#include <stdio.h>

int main(void) {
    int num1, num2;
    printf("Please enter two integers: ");
    scanf("%d %d", &num1, &num2);
    int sum = num1 + num2;

    // First, deal with num1.
    // Is it between -10 and 10?
    if (num1 >= -10 && num1 <= 10) {
        // Is it negative?
        if (num1 < 0) {
            printf("negative ");
            num1 *= -1;
        }
        // Print out whatever the digit is.
        if (num1 == 0) {
            printf("zero");
        }
        if (num1 == 1) {
            printf("one");
        }
        if (num1 == 2) {
            printf("two");
        }
        if (num1 == 3) {
            printf("three");
        }
        if (num1 == 4) {
            printf("four");
        }
        if (num1 == 5) {
            printf("five");
        }
        if (num1 == 6) {
            printf("six");
        }
        if (num1 == 7) {
            printf("seven");
        }
        if (num1 == 8) {
            printf("eight");
        }
        if (num1 == 9) {
            printf("nine");
        }
        if (num1 == 10) {
            printf("ten");
        }
    } else {
        // It wasn't between -10 and 10, so print out the number as is.
        printf("%d", num1);
    }

    // Now, print out the plus sign...
    printf(" + ");

    // Now, deal with num2
    // Is it between -10 and 10?
    if (num2 >= -10 && num2 <= 10) {
        // Is it negative?
        if (num2 < 0) {
            printf("negative ");
            num2 *= -1;
        }
        // Print out whatever the digit is
        if (num2 == 0) {
            printf("zero");
        }
        if (num2 == 1) {
            printf("one");
        }
        if (num2 == 2) {
            printf("two");
        }
        if (num2 == 3) {
            printf("three");
        }
        if (num2 == 4) {
            printf("four");
        }
        if (num2 == 5) {
            printf("five");
        }
        if (num2 == 6) {
            printf("six");
        }
        if (num2 == 7) {
            printf("seven");
        }
        if (num2 == 8) {
            printf("eight");
        }
        if (num2 == 9) {
            printf("nine");
        }
        if (num2 == 10) {
            printf("ten");
        }
    } else {
        // It wasn't between -10 and 10, so print out the number as is.
        printf("%d", num2);
    }

    // Now, print the equals sign.
    printf(" = ");


    // Now, deal with the sum
    // Is it between -10 and 10?
    if (sum >= -10 && sum <= 10) {
        // Is it negative?
        if (sum < 0) {
            printf("negative ");
            sum *= -1;
        }
        // Print out whatever the digit is.
        if (sum == 0) {
            printf("zero\n");
        }
        if (sum == 1) {
            printf("one\n");
        }
        if (sum == 2) {
            printf("two\n");
        }
        if (sum == 3) {
            printf("three\n");
        }
        if (sum == 4) {
            printf("four\n");
        }
        if (sum == 5) {
            printf("five\n");
        }
        if (sum == 6) {
            printf("six\n");
        }
        if (sum == 7) {
            printf("seven\n");
        }
        if (sum == 8) {
            printf("eight\n");
        }
        if (sum == 9) {
            printf("nine\n");
        }
        if (sum == 10) {
            printf("ten\n");
        }
    } else {
        // It wasn't between -10 and 10, so print out the number as is.
        printf("%d\n", sum);
    }

    return 0;
}
