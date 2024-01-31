// icecream: a sample solution.
// Tells Matilda whether she has enough money for icecream.

#include <stdio.h>

#define MAXIMUM_COST 10

int main(void) {
    int cost, scoops;

    // Read in the number of scoops, and the cost of each scoop.
    printf("How many scoops? ");
    scanf("%d", &scoops);

    printf("How many dollars does each scoop cost? ");
    scanf("%d", &cost);

    // Calculate the total cost.
    int totalCost = scoops * cost;

    // Does she have enough money? If so, print "You have enough money!"
    // Otherwise, print "Oh no, you don't have enough money :(".
    if (totalCost <= MAXIMUM_COST) {
        printf("You have enough money!\n");
    } else {
        printf("Oh no, you don't have enough money :(\n");
    }

    return 0;
}
