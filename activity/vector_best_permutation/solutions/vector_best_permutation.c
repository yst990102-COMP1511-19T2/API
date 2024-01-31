// Rearrange a Vector of Integers
//
// Written 16/3/2019
// by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1000

void get_ordering_permutation(int n, int vector[n], int permutation[n]);
void rearrange_vector(int n,  int vector[n], int permutation[n], int rearranged_vector[n]);
void reverse_index_vector(int n, int vector[n], int reverse_index[n]);
double euclidean_distance(int n, int vector1[n], int vector2[n]);
void print_array(int n, int array[n]);
int scanf_array(int n, int array[n]);

int main(void) {
    int vector_length;

    printf("Enter vector length: ");
    if (scanf("%d", &vector_length) != 1 || vector_length < 1) {
        fprintf(stderr, "Error: could read vector length\n");
        return 1;
    }

    int vector1[MAX_SIZE];
    printf("Enter vector1: ");
    if (scanf_array(vector_length, vector1) != vector_length) {
        fprintf(stderr, "Error: could read vector\n");
        return 1;
    }


    int vector2[MAX_SIZE];
    printf("Enter vector2: ");
    if (scanf_array(vector_length, vector2) != vector_length) {
        fprintf(stderr, "Error: could read vector\n");
        return 1;
    }

    int ordering_permutation1[MAX_SIZE];
    get_ordering_permutation(vector_length, vector1, ordering_permutation1);

    int ordering_permutation2[MAX_SIZE];
    get_ordering_permutation(vector_length, vector2, ordering_permutation2);

    int reverse_index[MAX_SIZE];
    reverse_index_vector(vector_length, ordering_permutation2, reverse_index);

    int permutation[MAX_SIZE];
    rearrange_vector(vector_length, ordering_permutation1, reverse_index, permutation);

    printf("Optimal permutation: ");
    print_array(vector_length, permutation);

    int rearranged_vector1[MAX_SIZE];
    rearrange_vector(vector_length, vector1, permutation, rearranged_vector1);

    double distance = euclidean_distance(vector_length, rearranged_vector1, vector2);
    printf("Euclidean distance = %lf\n", distance);

    return 0;
}

void get_ordering_permutation(int n, int vector[n], int permutation[n]) {
    int i = 0;
    while (i < n) {
        permutation[i] = i;
        i = i + 1;
    }

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        int j = 1;
        while (j < n) {
            if (vector[permutation[j]] < vector[permutation[j - 1]]) {
                int tmp = permutation[j];
                permutation[j] = permutation[j - 1];
                permutation[j - 1] = tmp;
                swapped = 1;
            }

            j = j + 1;
        }
    }
}


void rearrange_vector(int n,  int vector[n], int permutation[n], int rearranged_vector[n]) {
    int i = 0;
    while (i < n) {
        rearranged_vector[i] = vector[permutation[i]];
        i = i + 1;
    }
}


void reverse_index_vector(int n, int vector[n], int reverse_index[n]) {
    int i = 0;
    while (i < n) {
        reverse_index[vector[i]] = i;
        i = i + 1;
    }
}


// return the Euclidean Distance https://en.wikipedia.org/wiki/Euclidean_distance
// between vector 1 and vector 2

double euclidean_distance(int n, int vector1[n], int vector2[n]) {
    double difference_sum = 0;

    int i = 0;
    while (i < n) {
        double difference = vector1[i] - vector2[i];
        difference_sum += difference * difference;

        i = i + 1;
    }

    return sqrt(difference_sum);
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

// print n integers from array

void print_array(int n, int array[n]) {

    int i = 0;
    while (i < n) {
        printf("%d", array[i]);

        if (i < n - 1) {
            printf(" ");
        }

        i = i + 1;
    }
    printf("\n");
}
