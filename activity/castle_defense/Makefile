CC	?= clang
CFLAGS	?= -O3 -fvisibility=hidden
LDFLAGS	?= -s -static

.PHONY: all
all:	tests.zip castle_defense.zip
all:	castle_defense

TESTS	:= $(sort $(wildcard tests/*/*.in))
STARTER_CODE := realm.c realm.h test_realm.c main.c
tests.zip: ${TESTS}
	@zip -r $@ $^

castle_defense.zip: ${STARTER_CODE}
	@zip -r $@ $^
#
# We can't build `cs_paint' in prod:public because the rsync(1) from
# prod:private drops the solutions -- and apparently the binaries too.
#
ifeq (,$(findstring /public/, $(realpath ${PWD})))
castle_defense:	solutions/main.c solutions/realm.c
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

else
PRIVATE_DIR	= ../../../private

castle_defense:	${PRIVATE_DIR}/activities/castle_defense/castle_defense
	install $< -m 755 $@
endif

.PHONY:	clean
clean:
	-rm -f tests.zip
	-rm -f castle_defense.zip
	-rm -f castle_defense
