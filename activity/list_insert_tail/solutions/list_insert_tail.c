#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *insert_tail(int value, struct node *head);
struct node *last(struct node *head);
struct node *create_node(int data, struct node *next);
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

    struct node *new_head = insert_tail(value, head);
    print_list(new_head);

    return 0;
}


// Add a new node containing value at the end of the linked list.
// The head of the new list is returned.
struct node *insert_tail(int value, struct node *head) {
    struct node *new_node = malloc(sizeof (struct node));
    if (new_node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;

    // empty list is a special case
    // new node is now the head of the now 1 element list
    if (head == NULL) {
        return new_node;
    }

    struct node *l = last(head);
    l->next = new_node;
    return head;
}

// return pointer to last node in list
// NULL is returned if list is empty

struct node *last(struct node *head) {
    if (head == NULL) {
        return NULL;
    }

    struct node *n = head;
    while (n->next != NULL) {
        n = n->next;
    }
    return n;
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

