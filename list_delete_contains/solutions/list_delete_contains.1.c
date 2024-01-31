#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};


// Delete the first node in list the containing value - recursive version
// The deleted node is freed.
// If no node contains i, the list is not changed
// The head of the list is returned.

struct node *delete_contains(int value, struct node *head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->data == value) {
        struct node *new_head = head->next;
        free(head);
        return new_head;
    }
    head->next = delete_contains(value, head->next);
    return head;
}
