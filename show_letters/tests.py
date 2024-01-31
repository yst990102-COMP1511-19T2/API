#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=show_letters.c
compiler_args=-Dmain=_main show_letters.c test_show_letters.c -o test_show_letters
command=./test_show_letters

8 hello-world
4 hello-world
1 hello-world
32 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
1 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
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
    print('{0} command=./test_show_letters {2} "{1}" description=\'show_letters size={1} letters="{2}" \''.format(test_number, buffer_len, string))
    test_number += 1
