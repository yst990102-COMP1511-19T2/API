// Display a danish flag of arbitrary size.

#include <stdio.h>

#define BLOCK_WIDTH 3
#define BLOCK_HEIGHT 2
#define BASE_WIDTH (BLOCK_WIDTH * 3)
#define BASE_HEIGHT (BLOCK_HEIGHT * 2)

int main(void) {
    printf("Enter the flag size: ");
    int size;
    scanf("%d", &size);

    int height = BASE_HEIGHT * size;
    int width = BASE_WIDTH * size;

    int y = 0;
    while (y < height) {
        int x = 0;

        while (x < width) {
            int vertical = size * BLOCK_HEIGHT;
            int horizontal = size * BLOCK_WIDTH;

            if ((x == horizontal - 1) || (x == horizontal)) {
                printf(" ");
            } else if ((y == vertical - 1) || (y == vertical)) {
                printf(" ");
            } else {
                printf("#");
            }
            x += 1;
        }

        printf("\n");
        y += 1;
    }

    return 0;
}
