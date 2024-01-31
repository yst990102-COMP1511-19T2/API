#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// Delete the last node in list - recursive version
// The deleted node is freed.
// The head of the list is returned.

struct node *delete_last(struct node *head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        // list has one node, head is now NULL
        free(head);
        return NULL;
    }
    head->next = delete_last(head->next);
    return head;
}
