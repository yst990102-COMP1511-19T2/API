#!/usr/bin/python3
tests = """
max_cpu=3
no_reproduce_command=1
files=list_insert_tail.c
compiler_args=-Dmain=_main list_insert_tail.c test_list_insert_tail.c -o test_list_insert_tail
command=./test_list_insert_tail

pre_compile_command="../check_arrays_not_used.sh list_insert_tail.c"
pre_compile_command_shell=1

10
10 46
10 46 47
12 16 7 8 12 13 19 21
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_insert_tail {1} description="./list_insert_tail {1}"'.format(test_number, t))
    test_number += 1
