#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int count_even(struct node *head);
struct node *strings_to_list(int len, char *strings[]);

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = count_even(head);
    printf("%d\n", result);

    return 0;
}

// return the number of even values in a linked list
int count_even(struct node *head) {
    int num_even = 0;
    struct node *p = head;
    while (p != NULL) {
        if (p->data % 2 == 0) {
            num_even = num_even + 1;
        }
        p = p->next;
    }
    return num_even;
}

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}
