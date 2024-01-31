//  Written 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  read a line from stdin and and then an integer n
//  Print the character int the nth-position

#include <stdio.h>
#include <assert.h>

#define MAX_LINE_CHARS 256
int main(void) {
    char line[MAX_LINE_CHARS] = {0};
    fgets(line, MAX_LINE_CHARS, stdin);
    int i = 0;
    scanf("%d", &i);
    assert(i >= 0 && i < MAX_LINE_CHARS);
    printf("The character in position %d is '%c'\n", i, line[i]);
    return 0;
}
