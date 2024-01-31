// Compute Easter Sunday date
// Modified 3/3/2019 by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

// code for Butcher's Formula copied from
// http://smart.net/~mmontes/nature1876.html

// Note this program doesn't check whether
// the scanf call successfully reads a number.
// This is good practice but was not requested in the lab exercise
// because this isn't covered until later in COMP1511.

#include <stdio.h>

int main(void) {
    int a, b, c, d, e, f, g, h, i, k, l, m, p;
    int year, month, date;

    printf("Enter year: ");
    scanf("%d", &year);

    a = year % 19;
    b = year / 100;
    c = year % 100;
    d = b / 4;
    e = b % 4;
    f = (b + 8) / 25;
    g = (b - f + 1) / 3;
    h = (19 * a + b - d - g + 15) % 30;
    i = c / 4;
    k = c % 4;
    l = (32 + 2 * e + 2 * i - h - k) % 7;
    m = (a + 11 * h + 22 * l) / 451;
    month = (h + l - 7 * m + 114) / 31;  //  [3=March, 4=April]
    p = (h + l - 7 * m + 114) % 31;
    date = p + 1;  // (date in Easter Month)

    printf("Easter is ");

    if (month == 3) {
        printf("March");
    } else {
        printf("April");
    }

    printf(" %d in %d.\n", date, year);

    return 0;
}
