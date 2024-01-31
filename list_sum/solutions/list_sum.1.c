#include <stdio.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// Return sum of a linked list.
int sum(struct node *head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + sum(head->next);
}
