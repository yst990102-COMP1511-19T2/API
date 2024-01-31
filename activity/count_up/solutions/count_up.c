// Modified 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)

// Print integers between a lower and upper limit

#include <stdio.h>
#include <assert.h>

int main(void) {
    int lower, upper;

    printf("Enter lower: ");
    assert(scanf("%d", &lower) == 1);

    printf("Enter upper: ");
    assert(scanf("%d", &upper) == 1);

    int i = lower + 1;
    while (i < upper) {
        printf("%d\n", i);
        i = i + 1;
    }

    return 0;
}
