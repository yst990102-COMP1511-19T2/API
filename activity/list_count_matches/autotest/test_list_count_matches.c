#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


struct node {
    struct node *next;
    int          data;
};

int count_matches(struct node *head1, struct node *head2);
static void check_list_unchanged(char *name, struct node *head, int length, struct node **original_nodes, int *original_data);
static struct node *strings_to_list(int len, char *strings[], struct node *node[], int data[]);

static void print_list(struct node *head);
#undef main
int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    int length1 = dash_arg > 0 ? dash_arg - 1 : 0;
    int length2 = argc - dash_arg - 1;
    struct node *nodes1[length1+1];
    struct node *nodes2[length2+1];
    int data1[length1+1];
    int data2[length2+1];
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1], nodes1, data1);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1], nodes2, data2);

    printf("count_matches(");
    print_list(head1);
    printf(",");
    print_list(head2);
    printf(")\n");

    int return_value = count_matches(head1, head2);

    // If you're getting an error here,
    // you have returned an uninitialized value
    printf("count_matches returned: %d\n", return_value);

    printf("%d %d\n", length1, length2);
    check_list_unchanged("list1", head1, length1, nodes1, data1);
    check_list_unchanged("list2", head2, length2, nodes2, data2);
    return 0;
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

static void check_list_unchanged(char *name, struct node *head, int length, struct node **original_nodes, int *original_data) {
    struct node *p = head;
    for (int i = 0; i < length; i++) {
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
