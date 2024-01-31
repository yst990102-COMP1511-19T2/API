// Read a string and then print the letters one per line
// written by Andrew Taylor andrewt@cse.unsw.edu.au
// April 2018 as a COMP1511 lab exercise
//

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 5000

int is_palindrome(char line[]);

int main(void) {
    char line[MAXLINE] = {0};
    printf("Enter a string: ");
    fgets(line, MAXLINE, stdin);

    if (is_palindrome(line)) {
        printf("String is a palindrome\n");
    } else{
        printf("String is not a palindrome\n");
    }

    return 0;
}

// return 1 is line is palindromic, 0 otherwise
// line is terminated by either '\n' or '\0'
// case and non-alphabetic characters are ignored
// an empty line is considered a palindrome
int is_palindrome(char line[]) {
    int right = 0;
    while (line[right] != '\0' && line[right] != '\n') {

        right = right + 1;
    }

    right = right - 1;

    int left = 0;
    while (left < right) {
        int left_char = tolower(line[left]);
        int right_char = tolower(line[right]);
        if (!isalpha(left_char)) {
            left = left + 1;
        } else if (!isalpha(right_char)) {
            right = right - 1;
        } else if (left_char != right_char) {
            return 0;
        } else {
            left = left + 1;
            right = right - 1;
        }
    }

    return 1;
}