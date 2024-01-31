#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=strings_equal.c
compiler_args=-Dmain=_main strings_equal.c test_strings_equal.c -o test_strings_equal
command=./test_strings_equal

hello-world
hello-hello
hello-hell
hell-hello
hello-
-hello
-
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    t = t.split("-")
    print('{0} command=./test_strings_equal "{1}" "{2}" description=\'strings_equal("{1}", "{2}")\''.format(test_number, t[0], t[1]))
    test_number += 1
