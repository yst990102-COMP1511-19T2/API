// Read integers > 1 until EOF (or non-number)
// then print integers not exactly divisible by any other integer read
// 27/3/2018

#include <stdio.h>

#define MAX_NUMBERS 1001

void  print_divisble(int array_length, int array[]);

int main(void) {
    int numbers[MAX_NUMBERS];

    int n = 0;
    while (n < MAX_NUMBERS && scanf("%d", &numbers[n]) == 1) {
        n = n + 1;
    }

    printf("Indivisible numbers:");
    print_divisble(n, numbers);

    return 0;
}

// print integers in array which are not exactly divisible by any other integers in array

void print_divisble(int array_length, int array[]) {
    int i = 0;
    while (i < array_length) {
        int factors = 0;
        int j = 0;
        while (j < array_length) {
            if (array[i] % array[j] == 0) {
                factors = factors + 1;
            }
            j = j + 1;
        }
        if (factors == 1) {
            printf(" %d", array[i]);
        }
        i = i + 1;
    }
    printf("\n");
}
