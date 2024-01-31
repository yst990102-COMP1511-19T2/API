#!/usr/bin/python3
tests = """
max_cpu=10
ignore_case=True
ignore_white_space=True
compare_only_characters="0123456789"
no_reproduce_command=1
files=list_insert_head.c
compiler_args=-Dmain=_main list_insert_head.c test_list_insert_head.c -o test_list_insert_head
command=./test_list_insert_head

pre_compile_command="./check_arrays_not_used.sh list_insert_head.c"
pre_compile_command_shell=1

5 5 8 9 7 9 3 2 3 8 4
5 5 8 9 7 9 3 2 3 8 4
8 5 8 9 7 9 3 2 3 8 4
9 5 8 9 7 9 3 2 3 8 4
4 5 8 9 7 9 3 2 3 8 4
15 3 5 7 9 11 13 15
6 5
6 6
45
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_insert_head {1} description="./list_insert_head {1}"'.format(test_number, t))
    test_number += 1
