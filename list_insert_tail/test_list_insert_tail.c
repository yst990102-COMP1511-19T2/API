#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


struct node {
    struct node *next;
    int          data;
};


struct node *insert_tail(int value, struct node *head);
static void check_list(char *name, struct node *head, int original_list_length, struct node *original_nodes[], int original_data_fields[]);
static struct node *strings_to_list(int len, char *strings[], struct node *node[], int data[]);
static void print_list(struct node *head);
static void free_list(struct node *head);

#undef main
int main(int argc, char *argv[]) {
    int value = argc > 1 ? atoi(argv[1]) : 0;
    int length = argc - 2;
    struct node *nodes[argc]; // ensure non-zero length for VLA
    int data[argc];
    struct node *head = strings_to_list(length, argv + 2, nodes, data);

    printf("insert_tail(");
    printf("%d, ", value);
    print_list(head);
    printf(")\n");

    struct node *new_head = insert_tail(value, head);
    check_list("the list returned by insert_tail", new_head, length, NULL, data);

    printf("insert_tail returned: ");
    print_list(new_head);
    printf("\n");

    free_list(new_head);
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

static void free_list(struct node *head) {
    if (head != NULL) {
        free_list(head->next);
        free(head);
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


// You are not expected to understand the following code.
// It uses complex internal compiler features to
// print informative messages for student errors.

// detect clang address-sanitizer
#ifdef __has_feature
#if __has_feature(address_sanitizer)
// clang address-sanitizer
#define HAVE_ASAN
#endif
#endif

// detect gcc address-sanitizer
#ifdef __SANITIZE_ADDRESS__
#define HAVE_ASAN
#endif

#ifdef HAVE_ASAN
#include <sanitizer/asan_interface.h>
#include <stdint.h>
#include <string.h>

// return NULL if p is valid pointer to a malloc'ed region of size size
// otherwise return string describing pointer

static char *check_address_is_heap_pointer(void *p, size_t size) {
    if (!p)
        return NULL;
    if ((sizeof(p) == 8 && (uintptr_t)p == 0xbebebebebebebebe) || (sizeof(p) == 4 && (uintptr_t)p == 0xbebebebe))
        return "uninitialized";
    if (__asan_region_is_poisoned(p, size))
        return "invalid";
    char name[8]; // unused but required by __asan_locate_address
    void *region_address;
    size_t region_size;
    if (strcmp(__asan_locate_address(p, name, sizeof name, &region_address, &region_size), "heap") != 0)
        return "invalid (not from malloc)";
    return NULL;
}

// Use address-sanitizer and other methods to detect invalid pointers in a malloc'ed linked list
// name should be a string describing the list
// If original_nodes != NULL then every node is checked to ensure it is the array original_nodes
// If original_data_fields != NULL then every data field is checked to see if matches the element
// of original_data_fields at the same index as it node appears in original_nodes
// original_nodes and original_data_fields should be of length original_list_length

static void check_list(char *name, struct node *head, int original_list_length, struct node *original_nodes[], int original_data_fields[]) {
    char *pointer_description;
    if ((pointer_description = check_address_is_heap_pointer(head, sizeof *head))) {
        fprintf(stderr, "\nError: the head of %s is %s (%p)\n", name, pointer_description, head);
        exit(1);
    }
    int position = 0;
    for (struct node *n = head; n != NULL; n = n->next, position++) {
        // If you're getting an error here,
        // you have returned an invalid list
        int error = 0;
        if ((unsigned)n->data == 0xbebebebe) {
            fprintf(stderr, "Error: %s is invalid.\n", name);
            fprintf(stderr, "       The data field of node %d is uninitialized.\n", position);
            error = 1;
        }
        if ((pointer_description = check_address_is_heap_pointer(n->next, sizeof *(n->next)))) {
            if (!error)
                fprintf(stderr, "Error: %s is invalid.\n", name);
            fprintf(stderr, "       The next field of node %d is %s (%p).\n", position, pointer_description, n->next);
            error = 1;
        }
        if (error) {
            if (position) {
                fprintf(stderr, "       The data fields of nodes 0..%d in the list contain: [", position);
                for (struct node *m = head; m != n; m = m->next) {
                    fprintf(stderr, "%d, ", m->data);
                }
                fprintf(stderr, "%d]\n", n->data);
            }
            exit(1);
        }


        int position1 = 0;
        for (struct node *o = head;; o = o->next, position1++) {
            if (o == n->next) {
                if (position == position1) {
                    fprintf(stderr, "Error: %s is invalid.\n", name);
                    fprintf(stderr, "       The next field of node %d points to itself\n", position);
                } else  {
                    fprintf(stderr, "Error: %s is invalid.\n", name);
                    fprintf(stderr, "       The next field of node %d points to node %d.\n", position, position1);
                    fprintf(stderr, "       In other words, %s is circular.\n", name);
                }
                exit(1);
            }
            if (o == n)
                break;
        }

        if (original_list_length && original_nodes) {
            int i;
            for (i = 0; i < original_list_length; i++) {
                if (original_nodes[i] == n)
                    break;
            }

            if (i == original_list_length) {
                fprintf(stderr, "Error: %s is invalid.\n", name);
                fprintf(stderr, "       The node in position %d is not in the list it was given.\n", position);
                fprintf(stderr, "       Do not create new nodes with malloc\n");
                exit(1);
            }

            if (original_data_fields && original_data_fields[i] != n->data) {
                fprintf(stderr, "Error: %s is invalid.\n", name);
                fprintf(stderr, "       The node in position %d data field has been changed from %d to %d.\n", position, original_data_fields[i], n->data);
                fprintf(stderr, "       Do not change the data fields of nodes\n");
                exit(1);
            }
        }
    }
}
#else
static void check_list(char *name, struct node *head, int original_list_length, struct node *original_nodes[], int original_data_fields[]) {
}
#endif
