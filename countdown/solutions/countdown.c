// Count down from 10 to 0, using a loop.
// 2017-08-10   Alex Linker <{a.linker, z5061930}@unsw.edu.au>
//              Jashank Jeremy <{jashankj, z5017851}@cse.unsw.edu.au>

#include <stdio.h>

int main(int argc, char *argv[]) {
    // For this loop, we have a counter, which we'll call `num`.
    int num = 10;

    // And, as long as `num` is greater than or equal to zero:
    while (num >= 0) {
        // We print out the counter ---
        printf("%d\n", num);
        
        // --- and subtract one from it.
        num = num - 1;
    }

    return 0;
}
