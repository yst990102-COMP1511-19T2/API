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


struct pod *read_sightings(void);
struct pod *read_sighting(void);
struct date *read_date(void);

int count_orca_sightings(struct pod *first_pod);

int main(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    struct pod *first_pod = read_sightings();

    int n_orca_pods = count_orca_sightings(first_pod);
    printf("%d Orca sightings in %s\n", n_orca_pods, argv[1]);

    return 0;
}


//
// return the number of sightings of Orca
//
int count_orca_sightings(struct pod *first_pod) {
    // REPLACE THIS COMMENT WITH YOUR CODE
    // YOU ARE NOT PERMITTED TO USE ARRAYS
    // THIS FUNCTION SHOULD NOT CALL SCANF OR PRINTF
    // IT SHOULD JUST RETURN A VALUE
    return 42; // CHANGE ME
}


//
// DO NOT CHANGE THE FUNCTIONS BELOW HERE
//

// return linked list of sightings read from filename
// exit called if there is an error

struct pod *read_sightings(void) {
    struct pod *first_sighting = NULL;
    struct pod *last_sighting = NULL;

    struct pod *sighting = read_sighting();
    while (sighting != NULL) {
        if (first_sighting == NULL) {
            first_sighting = sighting;
            first_sighting->next = NULL;
        } else {
            last_sighting->next = sighting;
        }
        last_sighting = sighting;
        sighting = read_sighting();
    }

    return first_sighting;
}


// read a whale sighting (date, number of whales, whale species)
// return a pointer to a malloced struct containing these details
// return NULL if a sighting can not be read

struct pod *read_sighting(void) {
    struct pod *p = malloc(sizeof (struct pod));
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    p->next = NULL;

    p->when = read_date();
    if (p->when == NULL) {
        free(p);
        return NULL;
    }

    int n_scanned = scanf("%d", &(p->how_many));
    if (n_scanned != 1) {
        free(p);
        return NULL;
    }

    getchar();
    char species_buffer[MAX_SPECIES_NAME_LENGTH];
    if (fgets(species_buffer, MAX_SPECIES_NAME_LENGTH, stdin) == NULL) {
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

struct date *read_date(void) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    int n_scanned = scanf("%d/%d/%d", &(d->year), &(d->month), &(d->day));
    if (n_scanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}
