#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=string_length.c
compiler_args=-Dmain=_main string_length.c test_string_length.c -o test_string_length
command=./test_string_length

NULL
hello
hello world
hello-world
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
    print('{0} command=./test_string_length "{1}" description=\'string_length("{1}")\''.format(test_number, t))
    test_number += 1
