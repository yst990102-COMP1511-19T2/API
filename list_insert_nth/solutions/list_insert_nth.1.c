#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};


// Insert a new node containing value at position n of the linked list.
// if n == 0, node is inserted at start of list
// if n >= length of list, node is appended at end of list
// The head of the new list is returned.
// recursive version
struct node *insert_nth(int n, int value, struct node *head) {
    if (n > 0 && head != NULL) {
        head->next = insert_nth(n - 1, value, head->next);
        return head;
    }

    struct node *new_node = malloc(sizeof (struct node));
    if (new_node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = head;

    return new_node;
}

