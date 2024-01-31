// Created 2018-03-09 by Andrew Bennett <andrew.bennett@unsw.edu.au>
// as a lab example for COMP1511

// Calculate the percentage that a student scored in an exam.

#include <stdio.h>

int main(void) {
    int total_marks, student_marks;

    printf("Enter the total number of marks in the exam: ");
    scanf("%d", &total_marks);
    printf("Enter the number of marks the student was awarded: ");
    scanf("%d", &student_marks);

    double percentage;

    // Note: percentage has to be calculated as a double, otherwise the
    // answer will always be 0!
    // First: calculate the percentage (e.g. 0.1 for 10%).

    if (total_marks > 0) {
        percentage = (student_marks * 1.0) / total_marks;
    } else {
        percentage = 0;
    }

    // Then, convert it to a number out of 100, e.g. 10 for 10%.
    percentage = percentage * 100.0;

    // Print it out as a percentage, in the form "X%" where X has no
    // decimal places. We use "%.0lf" for this -- ".0" means nothing
    // after the decimal point, and "lf" means a double (long float).
    printf("The student scored %.0lf%% in this exam.\n", percentage);

    return 0;
}

