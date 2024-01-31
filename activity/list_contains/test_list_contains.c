#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


struct node {
    struct node *next;
    int          data;
};

int contains(int value, struct node *head);

static void print_list(struct node *head);
static void check_list_unchanged(char *name, struct node *head, int contains, struct node **original_node, int *original_data);
static struct node *strings_to_list(int len, char *strings[], struct node *node[], int data[]);

#undef main
int main(int argc, char *argv[]) {
    int value = argc > 1 ? atoi(argv[1]) : 0;
    int length = argc - 2;
    struct node *nodes[argc]; // ensure non-zero length for VLA
    int data[argc];
    struct node *head = strings_to_list(length, argv + 2, nodes, data);

    printf("contains(");
    printf("%d, ", value);
    print_list(head);
    printf(")\n");

    int return_value = contains(value, head);

    // If you're getting an error here,
    // you have returned an uninitialized value
    printf("contains returned: %d\n", return_value);


    check_list_unchanged("the list you are given", head, length, nodes, data);
    return 0;
}

static void check_list_unchanged(char *name, struct node *head, int contains, struct node **original_nodes, int *original_data) {
    struct node *p = head;
    for (int i = 0; i < contains; i++) {
        if (original_nodes[i] != p) {
            fprintf(stderr, "error: next field of node struct in %s changed\n", name);
            fprintf(stderr, "error: you are not permitted to change %s\n", name);
            exit(1);
        }
        if (original_data[i] != p->data) {
            fprintf(stderr, "error: data field of node struct in %s changed\n", name);
            fprintf(stderr, "error: you are not permitted to change %s\n", name);
            exit(1);
        }
        p = p->next;
    }
}

static void print_list(struct node *head) {
    printf("[");

    for (struct node *n = head; n != NULL; n = n->next) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]");
}

// create linked list from array of strings
static struct node *strings_to_list(int len, char *strings[], struct node *nodes[], int data[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
        nodes[i] = n;
        data[i] = n->data;
    }
    return head;
}
