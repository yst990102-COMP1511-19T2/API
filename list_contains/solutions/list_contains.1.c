#include <stdio.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// Return 1 if value occurs in linked list, 0 otherwise
int contains(int value, struct node *head) {
    if (head == NULL) {
        return 0;
    }
    return (head->data == value) || contains(value, head->next);
}
