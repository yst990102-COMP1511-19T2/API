#include <stdio.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// Return the n-th element of linked list.
// n == 0 returns first element, n == 1, second element, ....
int get_nth(int n, struct node *head) {
    assert(head != NULL && n >= 0);
    if (n == 0) {
        return head->data;
    }
    return get_nth(n - 1, head->next);
}
