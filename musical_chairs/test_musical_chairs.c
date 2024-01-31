#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 100

#undef player
#undef chair

// player in the game of chairs
struct player {
    char name[MAX_NAME_LENGTH];
};

// A node in a linked list of chairs
struct chair {
    struct player *sitting;
    struct chair *next;
};

// Student implemented function
struct chair *make_music(int turns, struct chair *chairs);

#undef be_seated
struct chair *be_seated(char name[MAX_NAME_LENGTH], struct chair *heir) {
    struct chair *c = malloc(sizeof(struct chair));
    c->sitting = malloc(sizeof(struct player));
    strcpy(c->sitting->name, name);
    c->next = heir;
    return c;
}

void kill_all_kings(struct chair *thrones) {
    while (thrones != NULL) {
        struct chair *next = thrones->next;
        free(thrones->sitting);
        free(thrones);
        thrones = next;
    }
}

#undef main

int main(int argc, char * argv[]) {
    struct chair *thrones = NULL;
    int i = 1;
    while (i < argc) {
        thrones = be_seated(argv[i], thrones);
        i++;
    }
    
    int music = -1;
    scanf("%d", &music);
    while (music != -1) {
        thrones = make_music(music, thrones);
        scanf("%d", &music);
    }
    
    kill_all_kings(thrones);
    return 0;
}

