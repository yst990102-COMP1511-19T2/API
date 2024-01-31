#!/bin/bash

# I don't know how Makefiles work.

# Purpose of this file: make sure that everything still works after a
# code change.

# pokedex.c + main.c -> starter_main
# pokedex.c + test_pokedex.c -> starter_test
# pokedex.c + automarking/ANDREWB_TEST_POKEDEX.c -> starter_andrewb_test

# solutions/pokedex.c + main.c -> soln_main
# solutions/pokedex.c + test_pokedex.c -> soln_test
# solutions/pokedex.c + automarking/andrewb_test_pokedex.c -> soln_andrewb_test


# Step 0: Setup

mkdir -p binaries

# Step 1: Compile

# starter code
echo "Compiling starter code"
dcc pokedex.c pokemon.c main.c -o binaries/starter_main -I.
dcc pokedex.c pokemon.c test_pokedex.c -o binaries/starter_test -I.
dcc pokedex.c pokemon.c automarking/andrewb_test_pokedex.c -o binaries/starter_andrewb_test -I.

# soln code
echo "Compiling solution"
dcc solutions/pokedex.c pokemon.c main.c -o binaries/soln_main -I.
dcc solutions/pokedex.c pokemon.c test_pokedex.c -o binaries/soln_test -I.
dcc solutions/pokedex.c pokemon.c automarking/andrewb_test_pokedex.c -o binaries/soln_andrewb_test -I.

# Step 2: Run Tests

echo "Running starter code + starter tests (shouldn't do much)"
./binaries/starter_test

read

echo -e "\n\n"
echo "Running starter code + andrewb tests (should fail pretty hard)"
./binaries/starter_andrewb_test

read

echo -e "\n\n"
echo "Running soln + starter tests (should pass)"
./binaries/soln_test

read

echo -e "\n\n"
echo "Running soln + andrewb tests (should pass)"
./binaries/soln_andrewb_test

read

echo -e "\n\n"
echo 'Now, go and run `starter_main` and `soln_main` yourself'
