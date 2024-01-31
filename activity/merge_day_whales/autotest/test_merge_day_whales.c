#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SPECIES_NAME_LENGTH 4096

// a struct to represent the date
// a whale pod sighting was made

struct date {
    int year;
    int month;
    int day;
};

// a struct to represent a sighting
// of a pod (group) of whales

struct pod {
    struct pod  *next;
    struct date *when;
    int         how_many;
    char        *species;
};


static struct pod *read_sightings_file(char filename[]);
static struct pod *read_sighting(FILE *f);
static struct date *read_date(FILE *f);
static void write_sightings_file(char filename[], struct pod *first_pod);
static void write_sighting(FILE *f, struct pod *p);
static void write_date(FILE *f, struct date *d);
static int length_list(struct pod *p);
static void free_sightings(struct pod *p);
static void check_list(struct pod *head, char *name, int original_list_length, struct pod *original_pods[]);

void merge_day_whales(struct pod *first_pod);

#undef main
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <old_file> <new_file>\n", argv[0]);
        return 1;
    }

    struct pod *first_pod = read_sightings_file(argv[1]);

    int length = length_list(first_pod);
    struct pod *original_pods[length + 1];
    struct pod *p = first_pod;
    for (int i = 0; i < length; i++) {
        original_pods[i] = p;
        p = p->next;
    }

    merge_day_whales(first_pod);

    check_list(first_pod, "the sightings list after merge_day_whales", length, original_pods);

    write_sightings_file(argv[2], first_pod);
    free_sightings(first_pod);

    return 0;
}

//
// DO NOT CHANGE THE FUNCTIONS BELOW HERE
//

// return linked list of sightings read from filename
// exit called if there is an error

static struct pod *read_sightings_file(char filename[]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(1);
    }

    struct pod *first_sighting = NULL;
    struct pod *last_sighting = NULL;

    struct pod *sighting = read_sighting(f);
    while (sighting != NULL) {
        if (first_sighting == NULL) {
            first_sighting = sighting;
            first_sighting->next = NULL;
        } else {
            last_sighting->next = sighting;
        }
        last_sighting = sighting;
        sighting = read_sighting(f);
    }

    return first_sighting;
}


// read a whale sighting (date, number of whales, whale species)
// return a pointer to a malloced struct containing these details
// return NULL if a sighting can not be read

static struct pod *read_sighting(FILE *f) {
    struct pod *p = malloc(sizeof (struct pod));
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    p->next = NULL;

    p->when = read_date(f);
    if (p->when == NULL) {
        free(p);
        return NULL;
    }

    int n_scanned = fscanf(f, "%d", &(p->how_many));
    if (n_scanned != 1) {
        free(p);
        return NULL;
    }

    fgetc(f);
    char species_buffer[MAX_SPECIES_NAME_LENGTH];
    if (fgets(species_buffer, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        free(p);
        return NULL;
    }
   // finish string at '\n' if there is one
    char *newline_ptr = strchr(species_buffer, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // also finish string at '\r' if there is one - files from Windows  will
    newline_ptr = strchr(species_buffer, '\r');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // malloc a char array long enough to hold species name
    // and copy species to it
    p->species = malloc(strlen(species_buffer) + 1);
    if (p->species == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(p->species, species_buffer);

    return p;
}


// read a date in year/month/day format from stream f
// return a pointer to a malloced date struct containing them
//  return NULL if a date can not be read

static struct date *read_date(FILE *f) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->day), &(d->month), &(d->year));
    if (n_scanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}


// print linked list of sightings to stream filename

static void write_sightings_file(char filename[], struct pod *first_pod) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(1);
    }

    struct pod *p = first_pod;
    while (p != NULL) {
        write_sighting(f, p);
        p = p->next;
    }
}


// print pod details to stream f

static void write_sighting(FILE *f, struct pod *p) {
    write_date(f, p->when);
    fprintf(f, " %2d %s\n", p->how_many, p->species);
}


// print date to  stream f

static void write_date(FILE *f, struct date *d) {
    fprintf(f, "%02d/%02d/%02d", d->day, d->month, d->year);
}


// free the list of sightings

void free_sightings(struct pod *p) {
    struct pod *curr = p;
    while (curr != NULL) {
        struct pod *next = curr->next;
        free(curr->species);
        free(curr->when);
        free(curr);
        curr = next;
    }
}

static int length_list(struct pod *p) {
    return p ? 0 : 1 + length_list(p->next);
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

static void check_list(struct pod *head, char *name, int original_list_length, struct pod *original_pods[]) {
    char *pointer_description;
    if ((pointer_description = check_address_is_heap_pointer(head, sizeof *head))) {
        fprintf(stderr, "\nError: the head of %s is %s (%p)\n", name, pointer_description, head);
        exit(1);
    }
    int position = 0;
    for (struct pod *n = head; n != NULL; n = n->next, position++) {
        // If you're getting an error here,
        // you have returned an invalid list
        int error = 0;
        if ((unsigned)n->how_many == 0xbebebebe) {
            fprintf(stderr, "Error: %s is invalid.\n", name);
            fprintf(stderr, "       The data how_many of pod %d is uninitialized.\n", position);
            error = 1;
        }
        if ((pointer_description = check_address_is_heap_pointer(n->next, sizeof *(n->next)))) {
            if (!error)
                fprintf(stderr, "Error: %s is invalid.\n", name);
            fprintf(stderr, "       The next field of pod %d is %s (%p).\n", position, pointer_description, n->next);
            error = 1;
        }

        if ((pointer_description = check_address_is_heap_pointer(n->species, sizeof *(n->species)))) {
            if (!error)
                fprintf(stderr, "Error: %s is invalid.\n", name);
            fprintf(stderr, "       The species field of pod %d is %s (%p).\n", position, pointer_description, n->species);
            error = 1;
        }

         if ((pointer_description = check_address_is_heap_pointer(n->when, sizeof *(n->when)))) {
            if (!error)
                fprintf(stderr, "Error: %s is invalid.\n", name);
            fprintf(stderr, "       The when field of pod %d is %s (%p).\n", position, pointer_description, n->when);
            error = 1;
        }

       if (error) {
            exit(1);
        }

        int position1 = 0;
        for (struct pod *o = head;; o = o->next, position1++) {
            if (o == n->next) {
                if (position == position1) {
                    fprintf(stderr, "Error: %s is invalid.\n", name);
                    fprintf(stderr, "       The next field of pod %d points to itself\n", position);
                } else  {
                    fprintf(stderr, "Error: %s is invalid.\n", name);
                    fprintf(stderr, "       The next field of pod %d points to pod %d.\n", position, position1);
                    fprintf(stderr, "       In other words, %s is circular.\n", name);
                }
                exit(1);
            }
            if (o == n)
                break;
        }

        if (original_list_length && original_pods) {
            int i;
            for (i = 0; i < original_list_length; i++) {
                if (original_pods[i] == n)
                    break;
            }

            if (i == original_list_length) {
                fprintf(stderr, "Error: %s is invalid.\n", name);
                fprintf(stderr, "       The pod in position %d is not in the list it was given.\n", position);
                fprintf(stderr, "       Do not create new pods with malloc\n");
                exit(1);
            }
        }
    }
}
#else
static void check_list(struct pod *head, char *name, int original_list_length, struct pod *original_pods[]) {
}
#endif
