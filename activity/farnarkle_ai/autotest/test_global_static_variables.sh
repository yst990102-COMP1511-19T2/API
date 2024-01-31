#!/bin/bash


dcc -c "$1" -o tmp.o 2>/dev/null || exit 1

their_variables=$(nm tmp.o | egrep -o "\s[Bb]\s.*"| cut -c 3-)
global_static_vars=$(echo -n "$their_variables" | wc -c)

rm tmp.o

if ((global_static_vars > 0)); then
    echo "You are not permitted to use global or static variables."
    echo "Please remove these from your code:"
    for x in $their_variables; do echo "   $x"; done
fi

