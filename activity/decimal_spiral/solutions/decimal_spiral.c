//decimal_spiral.c
//By Alex Rowell z5116848
//Written 20th March 2017
//A program to print a spiral of numbers, with the numbers increasing as it spirals outwards

#include <stdio.h>
#include <stdlib.h>


//These are for the direction of the current line being printed (to be explained below)
#define DIR_NONE 0
#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_UP 3
#define DIR_DOWN 4


//A key part of this implementation is splitting the numbers into lines
//These are the straight lines of numbers, with the first number coming from the line before
//There are 4 cases to deal with each line based on which direction it would go when spiraling inwards
//(For the example below 'r' is for lines going right, 'd' for lines going down, 'u' for lines going up and 'l' for lines going left)
//eg.
// rrrrr
// ----d
// urr-d
// u---d
// lllld

int main(void) {
    int num;

    printf("Enter size: ");
    if (!scanf("%d", &num) || num % 2 == 0) {
        //Did not get a number or the number is even, exit
        return 1;
    }


    // These are the sizes of the original lines, the right line starts
    // longer than the others since it doesn't have another direction that takes its first number
    // The up line starts shorter than the others since every time it gets to the upwards line the line
    // gets smaller
    int original_up_size = num - 3;
    int original_down_size = num - 1;
    int original_right_size = num + 1;
    int original_left_size = num - 1;



    //Determine the total number of numbers to write (so that it can count down)
    //This is done by simulating each side
    int total_stars = 0;

    int up_size = original_up_size;
    int down_size = original_down_size;
    int right_size = original_right_size;
    int left_size = original_left_size;

    while (up_size > 0) {
        total_stars = total_stars + up_size;
        up_size = up_size - 4; //Every go of the spiral, each side shrinks by 4
    }
    while (down_size > 0) {
        total_stars = total_stars + down_size;
        down_size = down_size - 4;
    }
    while (right_size > 0) {
        total_stars = total_stars + right_size;
        right_size = right_size - 4;
    }
    while (left_size > 0) {
        total_stars = total_stars + left_size;
        left_size = left_size - 4;
    }


    int row = 0;
    int col = 0;

    while (row < num) {
        col = 0;

        while (col < num) {

            int line_num = 0; // The number of line changes in the spiral before this line

            int offset = 0; // The number along the line this position is

            int line_dir = DIR_NONE; //The direction the line's going (or none if a dash should be printed)


            if (row <= num/2 && row % 2 == 0 && col >= row - 1 && col <= num-row - 1) { //Line going to the right
                line_dir = DIR_RIGHT;
                line_num = (row / 2 * 4);

                offset = col - row + 2;

            } else if (row > num/2 && row % 2 == 0 && col <= row && col >= num - row - 1) { //Line going to the left
                line_dir = DIR_LEFT;
                line_num = ((num-row-1)/2 * 4) + 2;

                offset = row - col;

            } else if (col <= num/2 && col % 2 == 0 && row >= col + 2 && row < num - col - 1) { //Line going upwards
                line_dir = DIR_UP;
                line_num = (col / 2 * 4) + 3;

                offset = num - col - 1 - row;
            } else if (col > num/2 && col % 2 == 0 && row <= col && row >= num - col) { //Line going downwards
                line_dir = DIR_DOWN;
                line_num = ((num-col-1)/2 * 4) + 1;

                offset = row - num + col + 1;
            }

            if (line_dir != DIR_NONE) {
                // Reset the number of stars in the first line of each type
                // For calculating the number to print out
                up_size = original_up_size;
                down_size = original_down_size;
                right_size = original_right_size;
                left_size = original_left_size;

                int num_so_far = 0; //The total numbers that have been printed so far in the spiral
                int i = 0;

                while (i < line_num) {
                    // Similar to calculating total number of numbers printed in the whole spiral
                    // but in this case only go up to the current line
                    if (i % 4 == 0) { // rightwards line
                        num_so_far = num_so_far + right_size;
                        right_size = right_size - 4;
                    } else if (i % 4 == 1) { // downwards line
                        num_so_far = num_so_far + down_size;
                        down_size = down_size - 4;
                    } else if (i % 4 == 2) { // leftwards line
                        num_so_far = num_so_far + left_size;
                        left_size = left_size - 4;
                    } else { // i % 4 == 3, upwards line
                        num_so_far = num_so_far + up_size;
                        up_size = up_size - 4;
                    }

                    i = i + 1;
                }

                num_so_far = num_so_far + offset; // Include the amount printed in the current line

                int to_print = total_stars - num_so_far; // Subtract num_so_far from total_stars as
                // the spiral should be counting down as it goes inwards
                printf("%d", to_print % 10); // Only take last digit of what to print

            } else {
                printf("-"); // Not part of spiral, just print a dash
            }
            col = col + 1;
        }
        printf("\n");
        row = row + 1;
    }

    return 0;
}
