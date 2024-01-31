#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=string_copy.c
compiler_args=-Dmain=_main string_copy.c test_string_copy.c -o test_string_copy
command=./test_string_copy

16 hello-world
8 hello-world
1 hello-world
32 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
64 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    t = t.split()
    buffer_len = t[0]
    string = " ".join(t[1:])
    print('{0} command=./test_string_copy {2} "{1}" description=\'string_copy source="{2}" destination_size={1}\''.format(test_number, buffer_len, string))
    test_number += 1
