#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};


// Add a new node containing value at the end of the linked list.
// The head of the new list is returned.
// recursive version
struct node *insert_tail(int value, struct node *head) {
    if (head != NULL) {
        head->next = insert_tail(value, head->next);
        return head;
    }

    struct node *new_node = malloc(sizeof (struct node));
    if (new_node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}

