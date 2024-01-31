#!/usr/bin/python3
tests = """
max_cpu=3
no_reproduce_command=1
files=list_insert_nth.c
compiler_args=-Dmain=_main list_insert_nth.c test_list_insert_nth.c -o test_list_insert_nth
command=./test_list_insert_nth

pre_compile_command="../check_arrays_not_used.sh list_insert_nth.c"
pre_compile_command_shell=1

0 10
1 10
2 10
42 10
0 10 46
1 10 46
2 10 46
42 10 46
0 10 46 47
1 10 46 47
2 10 46 47
42 10 46 47
0 12 16 7 8 12 13 19 21
1 12 16 7 8 12 13 19 21
4 12 16 7 8 12 13 19 21
7 12 16 7 8 12 13 19 21
8 12 16 7 8 12 13 19 21
9 12 16 7 8 12 13 19 21
42 12 16 7 8 12 13 19 21
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_insert_nth {1} description="./list_insert_nth {1}"'.format(test_number, t))
    test_number += 1
