//  Written 3/5/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  Reads lines and writes them out to stdout if they haven't been previously seen
//  Stops when it reaches the end of input.

#include <stdio.h>
#include <string.h>

#define MAX_LINE_CHARS 256
#define MAX_N_LINES 256

int main(void) {
    char lines[MAX_N_LINES][MAX_LINE_CHARS];

    int line_number = 0;
    while (fgets(lines[line_number], MAX_LINE_CHARS, stdin) != NULL && line_number < MAX_N_LINES) {
        int line_seen_previously = 0;
        int i = 0;
        while (i < line_number && !line_seen_previously) {
            if (strcmp(lines[line_number], lines[i]) == 0) {
                line_seen_previously = 1;
            }
            i = i + 1;
        }

        if (!line_seen_previously) {
            printf("%s",  lines[line_number]);
            line_number = line_number + 1;
        }
    }

    return 0;
}
