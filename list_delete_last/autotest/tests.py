#!/usr/bin/python3
tests = """
max_cpu=3
no_reproduce_command=1
compilers="dcc:dcc --valgrind:dcc --leak-check"
files=list_delete_last.c
compiler_args=-Dmain=_main list_delete_last.c test_list_delete_last.c -o test_list_delete_last
command=./test_list_delete_last

pre_compile_command="../../check_arrays_not_used.sh list_delete_last.c;./check_at_most_one_call_malloc.sh list_delete_last.c"
pre_compile_command_shell=1

3 1 4 1 5 9 2 6 5 3
2 7 1 8
45 56
10
NULL
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_delete_last {1} description="./list_delete_last {1}"'.format(test_number, t))
    test_number += 1
