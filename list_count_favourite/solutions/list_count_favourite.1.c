#include <stdio.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// Return the number of elements divisible by 17 in the linked list
int count_favourite(struct node *head) {
    if (head == NULL) {
        return 0;
    }
    return (head->data % 17 == 0) + count_favourite(head->next);
}
