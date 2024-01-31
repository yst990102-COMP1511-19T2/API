// Assignment 2 19T2 COMP1511: Castle Defense
// test_realm.c
//
// This file allows you to automatically test the functions you
// implement in realm.c.
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
// Version 1.1.0: Correctly make all functions in this file static.

#include <stdio.h>
#include <assert.h>

#include "realm.h"

static void test_new_realm(void);
static void test_print_realm(void);
static void test_add_location(void);

int main(void) {
    printf("\n================== Castle Defense Tests ==================\n");
    test_new_realm();
    test_print_realm();
    test_add_location();
}

////////////////////////////////////////////////////////////////////////
//                  Castle Defense Test Functions                     //
////////////////////////////////////////////////////////////////////////


// This function checks that a realm is actually being created.
static void test_new_realm(void) {
    printf(">> Testing new_realm\n");

    printf("... Creating new realm.\n");
    Realm realm = new_realm();

    printf("... Checking it is not null.\n");
    assert(realm != NULL);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will print out an empty realm - it should not crash.
static void test_print_realm(void) {
    printf(">> Testing print_realm\n");
    Realm realm = new_realm();

    printf("... This should show an empty realm - it should not crash.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations and try to print them.
static void test_add_location(void) {
    printf(">> Testing add_location.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "First_Location");
    add_location(realm, "Second_Location");
    add_location(realm, "Third_Location");

    printf("... This should show an realm with three extra locations.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}
