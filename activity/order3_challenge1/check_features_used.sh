#!/bin/bash

banned_statements=$(
    clang-check "$1" --ast-dump --extra-arg="-fno-color-diagnostics" -- 2>/dev/null|
    egrep -v ' _|extern'|
    egrep '^.*VarDecl.*\[[0-9]*\].*$' | 
    sed 's/.*VarDecl.*/ - Using Arrays/'|
    uniq
)


if test -n "$banned_statements"
then
    mv "$1" "$1.not_permitted"
    printf "#include <stdio.h>\nint main(void){\n    printf(\"Your code breaks the assignment rules. Check the error message above!\");\n}" > "$1"
cat << eof

Your program contains C features not permitted for this exercise.
$banned_statements

Your submission will not be tested.

eof
    exit 1
fi
