// A program to print a list of integers in reverse
// Written by Tom Kunc (t.kunc@unsw.edu.au)
// Created in 2019-06-23

#include <stdio.h>

#define MAX_NUMBERS 100

int main(void) {
    
    int scan_result, i = 0;
    int scanned_numbers[MAX_NUMBERS];

    printf("Enter numbers forwards: \n");
    while ((scan_result = scanf("%d", &(scanned_numbers[i])) == 1)) {
        i++;
    }
    printf("Reversed: \n");

    while (i > 0) {
        i--;
        printf("%d\n", scanned_numbers[i]);
    }

    return 0;
}
