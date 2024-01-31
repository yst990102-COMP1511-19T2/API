#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *strings_to_list(int len, char *strings[]);
int most_frequent(struct node *head);
int count_occurrances(int i, struct node *head);

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = most_frequent(head);
    printf("%d\n", result);

    return 0;
}

// return the value which occurs most frequently in a linked list
// if several values are equally most frequent
// the value that occurs earliest in the list is returned
int most_frequent(struct node *head) {
    int most_frequent_num = 0;
    int most_frequent_count = 0;
    struct node *p = head;
    while (p != NULL) {
        int count = count_occurrances(p->data, head);
        if (count > most_frequent_count) {
            most_frequent_num = p->data;
            most_frequent_count = count;
        }
        p = p->next;
    }
    return most_frequent_num;
}

// return the number of times i, occurs in a linked list
int count_occurrances(int i, struct node *head) {
    int num = 0;
    struct node *p = head;
    while (p != NULL) {
        if (p->data == i) {
            num = num + 1;
        }
        p = p->next;
    }
    return num;
}


// DO NOT CHANGE THIS FUNCTION

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
