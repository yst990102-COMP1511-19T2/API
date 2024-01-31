#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// Place the list into reverse order.
// The head of the list is returned.

struct node *reverse(struct node *head) {
    // lists of 0 or 1 node don't need to be changed
    if (head == NULL || head->next == NULL) {
        return head;
    }

    //reverse rest of list
    struct node *new_head = reverse(head->next);

    // head->next will be the last element in the reversed rest of list
    // append head to it
    head->next->next = head;
    head->next = NULL;

    return new_head;
}
