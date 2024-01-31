#include <stdio.h>

struct node {
    struct node *next;
    int          data;
};

// return 1 if i  occurs in list, 0 otherwise
int member(int i, struct node *head) {
    if (head == NULL) {
        return 0;
    } if (head->data == i) {
        return 1;
    } else {
        return member(i, head->next);
    }
}

// return the number of values which occur in both linked lists
// no value is repeated in either list
// cute, recursive solution
int intersection_size(struct node *head1, struct node *head2) {
    if (head1 == NULL) {
        return 0;
    } else {
        return member(head1->data, head2) + intersection_size(head1->next, head2);
    }
}

