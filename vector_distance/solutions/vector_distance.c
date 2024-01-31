// Compute the Euclidean Distance Between Two Vectors of Integers.
//
// Written 16/3/2019
// by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1000

int scanf_array(int n, int array[n]);
double euclidean_distance(int n, int vector1[n], int vector2[n]);

int main(void) {
    int vector_length;

    printf("Enter vector length: ");
    if (scanf("%d", &vector_length) != 1 || vector_length < 1) {
        fprintf(stderr, "Error: could not read vector length\n");
        return 1;
    }

    int vector1[MAX_SIZE];

    printf("Enter vector 1: ");
    if (scanf_array(vector_length, vector1) != vector_length) {
        fprintf(stderr, "Error: could not read vector 1\n");
        return 1;
    }

    int vector2[MAX_SIZE];
    printf("Enter vector 2: ");
    if (scanf_array(vector_length, vector2) != vector_length) {
        fprintf(stderr, "Error: could not read vector 2\n");
        return 1;
    }

    double distance = euclidean_distance(vector_length, vector1, vector2);

    printf("Euclidean distance = %lf\n", distance);
    return 0;
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

