// Rearrange a Vector of Integers
//
// Written 16/3/2019
// by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1000

int scanf_array(int n, int array[n]);
void print_permutation(int n, int vector[n], int permutation[n]);
int check_permutation(int n, int permutation[n]);

int main(void) {
    int vector_length;

    printf("Enter vector length: ");
    if (scanf("%d", &vector_length) != 1 || vector_length < 1) {
        fprintf(stderr, "Error: could read vector length\n");
        return 1;
    }

    int vector[MAX_SIZE];

    printf("Enter vector: ");
    if (scanf_array(vector_length, vector) != vector_length) {
        fprintf(stderr, "Error: could read vector\n");
        return 1;
    }

    int permutation[MAX_SIZE];
    printf("Enter permutation: ");
    if (scanf_array(vector_length, permutation) != vector_length) {
        fprintf(stderr, "Error: could read permutation\n");
        return 1;
    }

    if (check_permutation(vector_length, permutation)) {
        print_permutation(vector_length, vector, permutation);
    } else {
        printf("Invalid permutation\n");
    }

    return 0;
}


// print elements of vector using values in
// permutation as array indices

void print_permutation(int n, int vector[n], int permutation[n]) {
    int i = 0;
    while (i < n) {
        printf("%d ", vector[permutation[i]]);
        i = i + 1;
    }
    printf("\n");
}


// read 1 if all integers in permutation are >= 0 and < n
// return 0 otherwise
int check_permutation(int n, int permutation[n]) {
    int i = 0;
    while (i < n) {
        if (permutation[i] < 0 || permutation[i] >= n) {
            return 0;
        }

        i = i + 1;
    }

    return 1;
}


// read n integers into array
// return the number of integers read

int scanf_array(int n, int array[n]) {

    int i = 0;
    while (i < n) {
        int items_read = scanf("%d", &array[i]);

        if (items_read != 1) {
            return i;
        }

        i = i + 1;
    }

    return i;
}

