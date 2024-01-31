#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=count_even_list.c
compiler_args=-Dmain=_main count_even_list.c test_count_even_list.c -o test_count_even_list
command=./test_count_even_list

pre_compile_command="../../check_arrays_not_used.sh count_even_list.c;./check_at_most_one_call_malloc.sh count_even_list.c"
pre_compile_command_shell=1

3 1 4 1 5 9 2 6 5 3
1 1 1 1 1
8 1 2 3
1 1 1 1 1 1 1 1 1 1 2
2 1 3 5 7 9
10 11 12 13 14 15 16 17
11 12 13 14 15 16 17 18
10 11 12 13 14 15 16
11 12 13 14 15 16 17
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
    print('{0} command=./test_count_even_list {1} description="./count_even_list {1}"'.format(test_number, t))
    test_number += 1
