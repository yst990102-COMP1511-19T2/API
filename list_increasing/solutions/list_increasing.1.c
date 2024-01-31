#include <stdio.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// return 1 if values in a linked list in increasing order
// recursive solution

int increasing(struct node *head) {
    if (head == NULL || head->next == NULL) {
        return 1;
    } else if (head->data >= head->next->data)  {
        return 0;
    } else {
        return increasing(head->next);
    }
}
