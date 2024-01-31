#include <stdio.h>
#include <assert.h>

#define N_TILES 4
#define MAX_TILE 8
#define MAX_TURNS 100

void farnarkle_ai(int turn, int previous_guesses[MAX_TURNS][N_TILES], int farnarkles[MAX_TURNS], int arkles[MAX_TURNS], int guess[N_TILES]);

// read N_TILES tiles into array
static void read_tiles1(int tiles[N_TILES]) {
    for (int i = 0; i < N_TILES;i++) {
        assert(scanf("%d", &tiles[i]) == 1);
        assert(tiles[i] >= 1 && tiles[i] <= MAX_TILE);
    }
}

static void print_tiles1(int tiles[N_TILES]) {
    int i = 0;
    while (i < N_TILES) {
        printf("%d", tiles[i]);
        if (i < N_TILES - 1) {
            printf(" ");
        }
        i = i + 1;
    }
}

#undef main

int main(void) {
    int turn;
    int previous_guesses[MAX_TURNS][N_TILES];
    int farnarkles[MAX_TURNS];
    int arkles[MAX_TURNS];
    int guess[N_TILES];

    assert(scanf("%d", &turn) == 1);
    for (int i = 0; i < turn - 1; i++) {
        read_tiles1(previous_guesses[i]);
        assert(scanf("%d", &farnarkles[i]) == 1);
        assert(scanf("%d", &arkles[i]) == 1);
    }
    for (int i = 0; i < N_TILES; i++) {
        guess[i] = -1;
    }
    farnarkle_ai(turn, previous_guesses, farnarkles, arkles, guess);
    print_tiles1(guess);
    printf("\n");
    return 0;
}
