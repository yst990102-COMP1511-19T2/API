#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#undef node
#undef list_node

// A node in a linked list
struct node {
    int data;
    struct node *next;
};

// a list_node in a linked list. Each list_node
// contains a list of nodes.
struct list_node {
    struct node *my_list;
    struct list_node *next;
};

int has_diagonal(struct list_node *head);

struct node *make_list2(int length, int offset, char *argv[]) {
    struct node *head = malloc(sizeof (struct node));
    struct node *n = head;
    int i = 0;
    while (i < length) {
        n->data = strtol(argv[offset * length + i + 1], NULL, 10);
        if (i < length - 1) {
            // there are more nodes to make
            n->next = malloc(sizeof (struct node));
            n = n->next;            
        } else {
            n->next = NULL;
        }
        i++;
    }
    
    return head;
}

#undef main

int main(int argc, char *argv[]) {
    int side = sqrt(argc - 1);
    int i = 0;
    struct list_node *head = malloc(sizeof (struct list_node));
    struct list_node *l = head;
    while (i < side) {
        l->my_list = make_list2(side, i, argv);
        if (i < side - 1) {
            // there are more lists to make
            l->next = malloc(sizeof (struct list_node));
            l = l->next;            
        } else {
            l->next = NULL;
        }
        i++;
    }
    int result = has_diagonal(head);
    printf("%d\n", result);
    return 0;
}
