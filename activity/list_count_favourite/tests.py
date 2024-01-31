#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=list_count_favourite.c
compiler_args=-Dmain=_main list_count_favourite.c test_list_count_favourite.c -o test_list_count_favourite
command=./test_list_count_favourite

pre_compile_command="./check_arrays_not_used.sh list_count_favourite.c;./check_at_most_one_call_malloc.sh list_count_favourite.c"
pre_compile_command_shell=1

3 1 4 1 5 9
17 34 17 37 17 34 17
34
42
NULL
17 34 51 68 85 102 119 136 153
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_count_favourite {1} description="./list_count_favourite {1}"'.format(test_number, t))
    test_number += 1
