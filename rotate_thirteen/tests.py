#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=rotate_thirteen.c
compiler_args=-Dmain=_main rotate_thirteen.c test_rotate_thirteen.c -o test_rotate_thirteen
command=./test_rotate_thirteen

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
    print('{0} command=./test_rotate_thirteen "{1}" description=\'rotate_thirteen("{1}")\''.format(test_number, t))
    test_number += 1
