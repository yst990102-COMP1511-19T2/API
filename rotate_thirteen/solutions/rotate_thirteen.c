// Perform the ROT13 algorithm on a string -- sample solution.

#include <stdio.h>
#include <assert.h>

#include <string.h>


// Add your own #defines here
#define ALPHABET_LENGTH 26
#define LOWER_START     'a'
#define LOWER_END       (LOWER_START + ALPHABET_LENGTH)
#define UPPER_START     'A'
#define UPPER_END       (UPPER_START + ALPHABET_LENGTH)

#define MAX_LENGTH      256

void rotate_thirteen(char *string);
int rotate_one(int c);
int string_length(char *string);
int strings_equal(char *string_a, char *string_b);

// Add your own function porototypes here
int is_lower_letter(char l);
int is_upper_letter(char l);

int main(int argc, char *argv[]) {
    // Example tests
    char test_a[MAX_LENGTH] = "Hello, world!";
    rotate_thirteen(test_a);
    assert(strings_equal("Uryyb, jbeyq!", test_a));

    char test_b[MAX_LENGTH] = "abcdefghijklmnopqrstuvwxyz";
    rotate_thirteen(test_b);
    assert(strings_equal("nopqrstuvwxyzabcdefghijklm", test_b));

    char test_c[MAX_LENGTH] = "The quick brown fox jumped over the lazy dog.";
    rotate_thirteen(test_c);
    assert(strings_equal(
        "Gur dhvpx oebja sbk whzcrq bire gur ynml qbt.",
        test_c
    ));

    // Add your own tests here

    printf("All tests passed. You are awesome!\n");

    return 0;
}

// See: https://en.wikipedia.org/wiki/ROT13
void rotate_thirteen(char *string) {
    int l = 0;
    int length = string_length(string);
    while (l < length) {
        int i = 0;
        while (i < 13) {
            string[l] = rotate_one(string[l]);
            i = i + 1;
        }
        l = l + 1;
    }
}

// Use your code from the rotate_one warmup here.
int rotate_one(int c) {
    int letter_num = 0;
    int base = '\0';

    // Deal with lowercase and uppercase letters separately.
    if (is_lower_letter(c)) {
        letter_num = c - LOWER_START;
        base = LOWER_START;
    } else if (is_upper_letter(c)) {
        letter_num = c - UPPER_START;
        base = UPPER_START;
    } else {
        // If it's not lowercase or uppercase, it remains unchanged.
        return c;
    }

    // rotate by 1, wrap around alphabet
    letter_num = letter_num + 1;
    letter_num = letter_num % ALPHABET_LENGTH;

    return base + letter_num;
}

int string_length(char *string) {
    // Use your code from the string_length activity here.
    // Lazy tutor solution: use string.h
    return strlen(string);
}

int strings_equal(char *string_a, char *string_b) {
    // Use your code from the strings_equal activity here.
    // Lazy tutor solution: use string.h
    return strcmp(string_a, string_b) == 0;
}

int is_lower_letter(char l) {
    return (l >= LOWER_START && l < LOWER_END);
}

int is_upper_letter(char l) {
    return (l >= UPPER_START && l < UPPER_END);
}
