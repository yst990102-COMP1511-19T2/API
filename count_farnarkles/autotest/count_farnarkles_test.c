#include <stdio.h>
#include <assert.h>

#define N_TILES 4
#define MAX_TILE 8
#define MAX_TURNS 100

int count_farnarkles(int tiles1[N_TILES], int tiles2[N_TILES]);

// read N_TILES tiles into array
void read_tiles1(int tiles[N_TILES]) {
    for (int i = 0; i < N_TILES;i++) {
        assert(scanf("%d", &tiles[i]) == 1);
        assert(tiles[i] >= 1 && tiles[i] <= MAX_TILE);
    }
}

#undef main

int main(void) {
    int hidden_sequence[N_TILES];
    int guess[N_TILES];
    int hidden_sequence_copy[N_TILES];
    int guess_copy[N_TILES];

    read_tiles1(hidden_sequence);
    read_tiles1(guess);

    for (int i = 0; i < N_TILES; i++) {
        hidden_sequence_copy[i] = hidden_sequence[i];
        guess_copy[i] = guess[i];
    }

    printf("%d farnarkles\n", count_farnarkles(hidden_sequence, guess));
    for (int i = 0; i < N_TILES; i++) {
        if (hidden_sequence_copy[i] != hidden_sequence[i] || guess_copy[i] != guess[i]) {
            printf("Error: array changed by count_farnarkles\n");
            break;
        }
    }
    return 0;
}
