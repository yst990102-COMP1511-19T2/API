#include <stdio.h>
#include <assert.h>

#define N_TILES 4
#define MAX_TILE 8
#define MAX_TURNS 100

void play_farnarkle(int hidden_tiles[]);

// read N_TILES tiles into array
static void read_tiles1(int tiles[N_TILES]) {
    for (int i = 0; i < N_TILES;i++) {
        assert(scanf("%d", &tiles[i]) == 1);
        assert(tiles[i] >= 1 && tiles[i] <= MAX_TILE);
    }
}

#undef main

int main(void) {
    int hidden_tiles[N_TILES];
    int hidden_tiles_copy[N_TILES];

    read_tiles1(hidden_tiles);

    for (int i = 0; i < N_TILES; i++) {
        hidden_tiles_copy[i] = hidden_tiles[i];
    }

    play_farnarkle(hidden_tiles);

    for (int i = 0; i < N_TILES; i++) {
        if (hidden_tiles_copy[i] != hidden_tiles[i]) {
            printf("Error: array changed by play_farnarkle\n");
            break;
        }
    }
    return 0;
}
