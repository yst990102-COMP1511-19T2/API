// A program to track statistics of pets
// Written for COMP1511 tutorials by 
// Marc Chee (marc.chee@unsw.edu.au)
// July 2019

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 50

struct pet {
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int age;
    int weight;
};

void setup_pet(struct pet *my_pet);
void print_pet(struct pet *my_pet);
void strip_nl(char line[]);

int main(void) {
    struct pet new_pet;
    setup_pet(&new_pet);
    print_pet(&new_pet);
}

void setup_pet(struct pet *my_pet) {
    fgets(my_pet->name, MAX_NAME_LENGTH, stdin);
    strip_nl(my_pet->name);    
    fgets(my_pet->type, MAX_TYPE_LENGTH, stdin);
    strip_nl(my_pet->type);
    scanf("%d", &my_pet->age);
    scanf("%d", &my_pet->weight);    
}

void print_pet(struct pet *my_pet) {
    fputs(my_pet->name, stdout);
    printf(" is a ");
    fputs(my_pet->type, stdout);
    printf(" who is ");
    printf ("%d years old and weighs %dkg\n", my_pet->age, my_pet->weight);
}

void strip_nl(char line[]) {
    line[strlen(line) - 1] = '\0';
}
