// Show the dice range of a set of dice as well
// as their average roll
// Created 7/6/2019 by Marc Chee (marc.chee@unsw.edu.au)
// as a lab challenge

// Note this program doesn't check whether
// the scanf call successfully reads a number.
// This is good practice but was not requested in the lab exercise
// because this isn't covered until later in the course.

#include <stdio.h>

int main(void) {
    int diceSize;
    int numDice;
    int lowest;
    int highest;
    double average;
    
    // scan in dice stats
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &diceSize);
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &numDice);

    // calculate lowest and highest values
    lowest = numDice;
    highest = numDice * diceSize;
    
    // calculate average. The 2.0 makes the result a double
    average = (lowest + highest) / 2.0;
    
    if (diceSize <= 0 || highest <= 0) {
        printf("These dice will not produce a range.\n");
    } else {
        printf("Your dice range is %d to %d.\n", lowest, highest);
        printf("The average value is %lf\n", average);
    }

    return 0;
}
