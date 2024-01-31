#!/bin/bash

n_malloc_calls=$(
    clang-check "$1" --ast-dump --extra-arg=-fno-color-diagnostics -- 2>/dev/null|
    egrep -v ' _|extern'|
    egrep 'DeclRefExpr.*malloc'|
    wc -l
)


if ((n_malloc_calls > 1))
then
    mv "$1" "$1.not_permitted"

    # if stderr is a tty or DCC_COLORIZE_OUTPUT in env force ANSI color if we can
    # worth doing so students under exam pressure don't miss message
    if test \( -t 2 -o -z "DCC_COLORIZE_OUTPUT" \) -a -x /usr/bin/tput
    then
        if test -z "$TERM" || test "$TERM" = "dumb"
        then
            # force coloring (might break some places)
            export TERM=ansi
        fi
        normal="$(tput sgr0)"
        red="$(tput setaf 1)"
        magenta="$(tput setaf 5)"
    fi

    cat 1>&2 << eof
$red
Error: your code contains calls to malloc.

You are not permitted to call malloc for this exercise,
Your submission will not be tested.
$normal
eof
    exit 1
fi
