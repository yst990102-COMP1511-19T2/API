#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *delete_contains(int value, struct node *head);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s value list-elements\n", argv[0]);
        return 1;
    }
    int value = atoi(argv[1]);
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 2, &argv[2]);

    struct node *new_head = delete_contains(value, head);
    print_list(new_head);

    return 0;
}


// Delete the first node in the list containing i
// The deleted node is freed.
// If no node contains i, the list is not changed
// The head of the list is returned.

struct node *delete_contains(int value, struct node *head) {
    if (head == NULL) {
        // list is empty no node to delete
        return NULL;
    }
    if (head->data == value) {
        struct node *new_head = head->next;
        free(head);
        return new_head;
    }
    if (head->next == NULL) {
        return head;
    }

    struct node *n = head;
    // find node before first node containing i
    while (n->next->next != NULL && n->next->data != value) {
        n = n->next;
    }

    if (n->next->data == value) {
        struct node *new_next = n->next->next;
        free(n->next);
        n->next = new_next;
    }
    return head;
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

// print linked list
void print_list(struct node *head) {
    printf("[");

    for (struct node *n = head; n != NULL; n = n->next) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

