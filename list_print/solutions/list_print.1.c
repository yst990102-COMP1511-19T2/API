#include <stdio.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// print a linked list in this format:
// 17 -> 34 -> 51 -> 68 -> X
void print(struct node *head) {
    if (head == NULL) {
        printf("X\n");
    }
    printf("%d -> ", head->data);
    print(head->next);
}
