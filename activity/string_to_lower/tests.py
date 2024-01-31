#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=string_to_lower.c
compiler_args=-Dmain=_main string_to_lower.c test_string_to_lower.c -o test_string_to_lower
command=./test_string_to_lower

NULL
hello
hello world
Hello-World
abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_string_to_lower "{1}" description=\'string_to_lower("{1}")\''.format(test_number, t))
    test_number += 1
