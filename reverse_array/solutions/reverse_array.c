// A program to print a list of integers in reverse
// Written by Tom Kunc (t.kunc@unsw.edu.au)
// Created in 2019-06-23

#include <stdio.h>

#define MAX_NUMBERS 100

int main(void) {
    
    int i = 0;
    int did_scan_something = 0;
    int scanned_value;
    int scanned_numbers[MAX_NUMBERS];

    printf("Enter numbers forwards:\n");

    while (scanf("%d", &scanned_value) == 1) {
        scanned_numbers[i] = scanned_value;
        did_scan_something = 1;
        i++;
    }
    
    printf("Reversed:\n");

    while (i > 0 && did_scan_something) {
        i--;
        printf("%d\n", scanned_numbers[i]);
    }

    return 0;
}
