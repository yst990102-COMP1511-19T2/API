#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#undef node

// A node in a linked list
struct node {
    int data;
    struct node *next;
};

struct node *remove_disorder(struct node *head);
void printList2(struct node *head);

struct node *make_list2(int length, char *argv[]) {
    struct node *head = malloc(sizeof (struct node));
    struct node *n = head;
    int i = 0;
    while (i < length) {
        n->data = strtol(argv[i + 1], NULL, 10);
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
    int length = argc - 1;
    struct node *head = make_list2(length, argv);
    head = remove_disorder(head);
    printList2(head);
    return 0;
}

void printList2(struct node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
