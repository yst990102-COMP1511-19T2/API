// Solution to week 4 boxes task
// By Curtis Millar
// Written on 2017-08-12

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("How many boxes: ");
    int numBoxes;
    if (scanf("%d", &numBoxes) != 1) {
        printf("Unable to read number");
        exit(0);
    }

    // Each box has a gap in the middle
    // so the width & height are
    int size = numBoxes * 4 - 1;

    int y = 0;
    while (y < size) {

        // Vertical loop
        int x = 0;
        while (x < size) {
            int xInverse = (size - 1) - x;
            int yInverse = (size - 1) - y;

            if ((y == x) || (y == xInverse)) {
                // On diagonals
                if (y % 2 == 0) {
                    printf("1");
                } else {
                    printf("0");
                }
            } else if ((y > x) && (y < xInverse) && (x % 2 == 0)) {
                // left side
                printf("1");
            } else if ((y < x) && (y > xInverse) && (x % 2 == 0)) {
                // right side
                printf("1");
            } else if ((x > y) && (x < yInverse) && (y % 2 == 0)) {
                // top side
                printf("1");
            } else if ((x < y) && (x > yInverse) && (y % 2 == 0)) {
                // bottom side
                printf("1");
            } else {
                printf("0");
            }
            x = x + 1;
        }

        printf("\n");
        y = y + 1;
    }

    return 0;
}
