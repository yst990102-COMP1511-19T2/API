// Assignment 1 19T2 COMP1511: CS Paint
// paint.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0 (2019-06-22): Assignment released.

#include <stdio.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define WHITE 4

// IF YOU NEED MORE #defines ADD THEM HERE


// Provided helper functions:
// Print out the canvas.
void printCanvas(int canvas[N_ROWS][N_COLS]);
// Set the entire canvas to be blank.
void setBlankCanvas(int canvas[N_ROWS][N_COLS]);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE


int main(void) {
    int canvas[N_ROWS][N_COLS];

    setBlankCanvas(canvas);

    // TODO: Add your code here!

    printCanvas(canvas);
}



// ADD CODE FOR YOUR FUNCTIONS HERE



// Prints the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the printCanvas function.
void printCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the setBlankCanvas function.
void setBlankCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}
