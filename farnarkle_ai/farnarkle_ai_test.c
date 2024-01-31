#include <stdio.h>
#include <assert.h>

#define N_TILES 4
#define MAX_TILE 8
#define MAX_TURNS 100

int count_farnarkles(int tiles1[N_TILES], int tiles2[N_TILES]);
int count_arkles(int tiles1[N_TILES], int tiles2[N_TILES]);
void farnarkle_ai(int turn, int previous_guesses[MAX_TURNS][N_TILES], int farnarkles[MAX_TURNS], int arkles[MAX_TURNS], int guess[N_TILES]);

static void read_tiles1(int tiles[N_TILES]);
static int test_farnarkle_ai1(int hidden_tiles[N_TILES]);

#undef main

int main(void) {
    int hidden_tiles[N_TILES];
    read_tiles1(hidden_tiles);
    test_farnarkle_ai1(hidden_tiles);
    return 0;
}

static int test_farnarkle_ai1(int hidden_tiles[N_TILES]) {
    int guesses[MAX_TURNS][N_TILES] = {{0}};
    int farnarkles[MAX_TURNS] = {0};
    int arkles[MAX_TURNS] = {0};
    int turn_limit =  MAX_TILE * N_TILES;

    int turn = 0;
    while (turn <= turn_limit) {
        int i = 0;
        while (i < N_TILES) {
            guesses[turn][i] = -1;
            i = i + 1;
        }

        farnarkle_ai(turn + 1, guesses, farnarkles, arkles, guesses[turn]);

        int j = 0;
        while (j < N_TILES) {
            if (guesses[turn][j] < 1 || guesses[turn][j] > MAX_TILE) {
                printf("Invalid guess\nGame ended\n");
                return 0;
            }
            j = j + 1;
        }

        farnarkles[turn] = count_farnarkles(hidden_tiles, guesses[turn]);
        arkles[turn] = count_arkles(hidden_tiles, guesses[turn]);

        if (farnarkles[turn] == N_TILES) {
            printf("Farnarkle AI guessed the tiles\n");
            return turn + 1;
        }
        turn = turn + 1;
    }
    printf("Turn limit of %d turns exceeded\nGame ended\n", turn_limit);
    return turn + 1;

}

// read N_TILES tiles into array
static void read_tiles1(int tiles[N_TILES]) {
    for (int i = 0; i < N_TILES;i++) {
        assert(scanf("%d", &tiles[i]) == 1);
        assert(tiles[i] >= 1 && tiles[i] <= MAX_TILE);
    }
}


