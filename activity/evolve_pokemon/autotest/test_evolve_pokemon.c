#include <stdio.h>
#include <stdlib.h>

#undef MAX_NAME_SIZE
#define MAX_NAME_SIZE 50

#define MAX_POKEMON 10

#undef pokemon
struct pokemon {
    char name[MAX_NAME_SIZE];
    struct pokemon *evolution;
};

struct pokemon *create_pokemon(char name[MAX_NAME_SIZE]);
void evolve_pokemon(struct pokemon *base, struct pokemon *evolution);
void print_evolution(struct pokemon *p);

#undef main

int main(int argc, char *argv[]) {
    int numPokemon = argc - 1;
    struct pokemon *p_pointers[MAX_POKEMON];
    
    int i = 1;
    while (i < argc) {
        p_pointers[i - 1] = create_pokemon(argv[i]);
        i++;
    }
    i = 0;
    while(i < numPokemon - 1) {
        evolve_pokemon(p_pointers[i], p_pointers[i + 1]);
        i++;
    }
    print_evolution(p_pointers[0]);
    
    return 0;
}
