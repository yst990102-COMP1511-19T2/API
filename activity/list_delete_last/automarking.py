#!/usr/bin/python3
tests = """
max_cpu=10
ignore_case=True
ignore_white_space=True
compare_only_characters="0123456789"
no_reproduce_command=1
compilers="dcc:dcc --valgrind:dcc --leak-check"
files=list_delete_last.c
compiler_args=-Dmain=_main list_delete_last.c test_list_delete_last.c -o test_list_delete_last
command=./test_list_delete_last

pre_compile_command="./check_arrays_not_used.sh list_delete_last.c;./check_at_most_one_call_malloc.sh list_delete_last.c"
pre_compile_command_shell=1

NULL
45
6 5
1 2 3
5 5 5 5
6 5 4 3 2 1
1 2 3 4 5 6 7
3 5 7 9 11 13 15
5 8 9 7 9 3 2 3 8 4
1 2 3 4 5 6 7 1 2 3 4 5 6 7 1 2 3 4 5 6 7
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
