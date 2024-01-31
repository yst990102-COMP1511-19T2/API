// CONVERT A STRING TO UPPERCASE
// CREATED BY
//  ... (Z0000000)
//  ... (Z0000000)
// CREATED ON 2017-08-??
// TUTOR'S NAME (DAYHH-LAB)

#include <stdio.h>

void string_to_upper(char *buffer);
int uppercase(int c);

int main(int argc, char *argv[]) {
    /// THIS WON'T WORK!
    ///
    /// str only points to a string literal, which it is not legal to change.
    /// If you attempt to modify it on Linux you will get a runtime error.
    //
    // char *str = "Hello!"
    // string_to_upper(str)

    char str[] = "Seventeen...  SEVENTEEN, I SAY!";
    string_to_upper(str);
    printf("%s\n", str);

    return 0;
}

// Convert the characters in `buffer` to upper case
void string_to_upper(char *buffer) {
    int i = 0;
    while (buffer[i] != '\0') {
        buffer[i] = uppercase(buffer[i]);
        i = i + 1;
    }
}

int uppercase(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    } else {
        return c;
    }
}
