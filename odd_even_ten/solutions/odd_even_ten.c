//Read MAX_NUMBERS integers and print odd and even integers on separate lines
// Andrew Taylor - andrewt@unsw.edu.au
// 27/3/2018
//
// Note for simplicity we are assuming scanf succeeds in reading an integer.
// A robust program would check that scanf returns 1 to indicate an integer was read.
// e.g. assert(scanf("%d", &numbers[i]) == 1)


#include <stdio.h>

#define MAX_NUMBERS 10

int main(void) {
    int numbers[MAX_NUMBERS] = {0};

    int i = 0;
    while (i < MAX_NUMBERS) {
        scanf("%d", &numbers[i]);
        i = i + 1;
    }

    printf("Odd numbers were:");
    int j = 0;
    while (j < MAX_NUMBERS) {
        if (numbers[j] % 2 == 1) {
            printf(" %d", numbers[j]);
        }
        j = j + 1;
    }
    printf("\n");

    printf("Even numbers were:");
    int k = 0;
    while (k < MAX_NUMBERS) {
        if (numbers[k] % 2 == 0) {
            printf(" %d", numbers[k]);
        }
        k = k + 1;
    }
    printf("\n");

    return 0;
}
