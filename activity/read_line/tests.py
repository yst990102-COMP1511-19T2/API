#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=read_line.c
compiler_args=-Dmain=_main read_line.c test_read_line.c -o test_read_line
command=./test_read_line

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
    input = " ".join(t[1:])
    print('{0} command=./test_read_line {1} stdin="{2}\\n" description=\'read_line buffer_len={1} input="{2}"\''.format(test_number, buffer_len,input))
    test_number += 1
