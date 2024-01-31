#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=list_get_nth.c
compiler_args=-Dmain=_main list_get_nth.c test_list_get_nth.c -o test_list_get_nth
command=./test_list_get_nth

pre_compile_command="../check_arrays_not_used.sh list_get_nth.c;../check_at_most_one_call_malloc.sh list_get_nth.c"
pre_compile_command_shell=1

0 56
0 42 46
1 42 46
0 16 7 8 12 13 19 21 12
1 16 7 8 12 13 19 21 12
2 16 7 8 12 13 19 21 12
7 16 7 8 12 13 19 21 12
8 16 7 8 12 13 19 21 12
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_get_nth {1} description="./list_get_nth {1}"'.format(test_number, t))
    test_number += 1
