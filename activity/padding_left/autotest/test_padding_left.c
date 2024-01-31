#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 100

#undef character_node

struct character_node {
    char data;
    struct character_node *next;
};

// Student implemented function
struct chair *pad_left(struct character_node *characters, char pad_character);

#undef string_to_characters

struct character_node *string_to_characters(char* string) {
    struct character_node *list_head = NULL;
    
    int curr_char = strlen(string) - 1;
    while (curr_char >= 0) {
        struct character_node *n = malloc(sizeof(struct character_node));
        n->data = string[curr_char];
        n->next = list_head;
        list_head = n;
        curr_char -= 1;
    }

    return list_head;
}

#undef print_characters

void print_characters(struct character_node *c) {
    while (c != NULL) {
        putchar(c->data);
        c = c->next;
    }
    putchar('\n');
}

#undef free_characters

void free_characters(struct character_node *c) {
    if (c == NULL) {
        return;
    }
    free_characters(c->next);
    free(c);
}

#undef main

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Usage: %s a_string_to_pad\n", argv[0]);
        return 0;
    }
    char *string = argv[1];
    struct character_node *characters = string_to_characters(string);
    int pad_character;
    while ((pad_character = getchar()) != -1){
        if (pad_character == '\n') {
            print_characters(characters);
        } else {
            pad_left(characters, pad_character);
        }
    }
    free_characters(characters);
        
    return 0;
}
