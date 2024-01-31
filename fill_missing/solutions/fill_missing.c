#include <stdio.h>

#define MAX_NUMBERS 10000

int present_in_array(int x, int length, int array[length]);

int main(void) {
    int numbers[MAX_NUMBERS];
    int biggest = -1;

    int n_numbers = 0;
    while (n_numbers < MAX_NUMBERS && scanf("%d", &numbers[n_numbers]) == 1) {
        if (numbers[n_numbers] > biggest) {
            biggest = numbers[n_numbers];
        }
        n_numbers = n_numbers + 1;
    }

    int i = 1;
    while (i < biggest) {
        if (!present_in_array(i, n_numbers, numbers)) {
            printf("%d ", i);
        }
        i = i + 1;
    }
    printf("\n");
}

int present_in_array(int x, int length, int array[length]) {
    int i = 0;
    while (i < length) {
        if (array[i] == x) {
            return 1;
        }
        i = i + 1;
    }
    return 0;
}
