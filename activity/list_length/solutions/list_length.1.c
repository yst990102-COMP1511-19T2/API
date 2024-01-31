#include <stdio.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// Return length of a linked list.
int length(struct node *head) {
    if (head == NULL) {
        return 0;
    }
    return 1 + length(head->next);
}
