SUPPLIED_FILES=main.c pokedex.c pokedex.h pokemon.c pokemon.h test_pokedex.c
REFERENCE_IMPLEMENTATION_SOURCE=main.c pokemon.c ../../../private/activities/pokedex/solutions/pokedex.c

all:	reference_implementation pokedex.zip

reference_implementation: $(SUPPLIED_FILES) $(REFERENCE_IMPLEMENTATION_SOURCE) Makefile
	clang -o $@ -O3 -s $(REFERENCE_IMPLEMENTATION_SOURCE)
	chmod 755 $@

pokedex.zip: $(SUPPLIED_FILES) Makefile
	zip -qr $@ $(SUPPLIED_FILES)
	chmod 644 $@
