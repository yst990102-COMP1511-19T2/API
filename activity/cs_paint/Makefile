PYTHON	?= python3
CC	?= clang
CFLAGS	?= -O3 -fvisibility=hidden
LDFLAGS	?= -s -static

.PHONY: all
all:	tests.zip
all:	cs_paint cache.pickle

TESTS	:= $(sort $(wildcard tests/*/*.in))
tests.zip: ${TESTS}
	@zip -r $@ $^

#
# We can't build `cs_paint' in prod:public because the rsync(1) from
# prod:private drops the solutions -- and apparently the binaries too.
#
ifeq (,$(findstring /public/, $(realpath ${PWD})))
cs_paint:	hidden_solutions/paint.c
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

cache.pickle:	cs_paint canvas canvas.sh \
		build_cache.py cs_paint_template_variables.py \
		index.html
	${PYTHON} build_cache.py
else
PRIVATE_DIR	= ../../../private

cs_paint:	${PRIVATE_DIR}/activities/cs_paint/cs_paint
	install $< -m 755 $@
cache.pickle:	${PRIVATE_DIR}/activities/cs_paint/cache.pickle
	install $< -m 644 $@
endif

.PHONY:	clean
clean:
	-rm -f tests.zip
	-rm -f cs_paint
	-rm -f cache.pickle
