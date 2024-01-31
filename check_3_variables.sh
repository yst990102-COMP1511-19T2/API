#!/bin/bash

variables=$(
    clang-check "$1" --ast-dump --extra-arg="-fno-color-diagnostics" -- 2>/dev/null|
    egrep -v ' _|extern'|
    egrep -- "-VarDecl"|
    sed "s/.* used //;s/.*:[0-9]* *//;s/'//g;s/ .*//"
    )

n_variables=$(echo "$variables"|wc -l)

if (($n_variables > 3))
then
    mv "$1" "$1.not_permitted"
    echo "#include <stdio.h>\nint main(void){\n    printf(\"Your code breaks the assignment rules. Check the error message above!\\n\");\n}" > "$1"
    cat <<eof

Your program contains $n_variables variables:
$variables

Only 3 variables are permitted for this exercise.
Your submission will not be tested.

eof
    exit 1
fi
