#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=show_terminated_letters.c
compiler_args=-Dmain=_main show_terminated_letters.c test_show_terminated_letters.c -o test_show_terminated_letters
command=./test_show_terminated_letters

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
    print('{0} command=./test_show_terminated_letters "{1}" description=\'show_terminated_letters("{1}")\''.format(test_number, t))
    test_number += 1
