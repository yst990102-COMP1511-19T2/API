#include <stdio.h>

struct node {
    struct node *next;
    int          data;
};

// return the number of even values in a linked list
// cute, recursive solution
int count_even(struct node *head) {
    if (head == NULL) {
        return 0;
    } else {
        return (head->data % 2) + count_even(head->next);
    }
}

