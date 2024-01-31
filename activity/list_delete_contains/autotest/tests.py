#!/usr/bin/python3
tests = """
max_cpu=3
no_reproduce_command=1
compilers="dcc:dcc --valgrind:dcc --leak-check"
files=list_delete_contains.c
compiler_args=-Dmain=_main list_delete_contains.c test_list_delete_contains.c -o test_list_delete_contains
command=./test_list_delete_contains

pre_compile_command="./check_arrays_not_used.sh list_delete_contains.c;./check_at_most_one_call_malloc.sh list_delete_contains.c"
pre_compile_command_shell=1

12 16 7 8 12 13 19 21 12
16 16 7 8 12 13 19 21 12
7 16 7 8 12 13 19 21 12
21 16 7 8 12 13 19 21 12
4 1 2 3 4
45 56
46 46
10
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_delete_contains {1} description="./list_delete_contains {1}"'.format(test_number, t))
    test_number += 1
