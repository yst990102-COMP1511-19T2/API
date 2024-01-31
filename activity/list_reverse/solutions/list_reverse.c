#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *reverse(struct node *head);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    struct node *new_head = reverse(head);
    print_list(new_head);

    return 0;
}

// Place the list into reverse order.
// The head of the list is returned.

struct node *reverse(struct node *head) {
    if (head == NULL) {
        return NULL;
    }
    struct node *previous = NULL;
    struct node *x = head;
    while (x != NULL) {
        struct node *y = x->next;
        x->next = previous;
        previous = x;
        x = y;
    }
    return previous;
}

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}

// print linked list
void print_list(struct node *head) {
    printf("[");

    for (struct node *n = head; n != NULL; n = n->next) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

