#!/usr/bin/python3
tests = """
max_cpu=10
ignore_case=True
ignore_white_space=True
compare_only_characters="0123456789"
no_reproduce_command=1

files=list_count_favourite.c
compiler_args=-Dmain=_main list_count_favourite.c test_list_count_favourite.c -o test_list_count_favourite
command=./test_list_count_favourite

pre_compile_command="./check_arrays_not_used.sh list_count_favourite.c;./check_at_most_one_call_malloc.sh list_count_favourite.c"
pre_compile_command_shell=1

13  11 15 19 11 14
13 19 14 15
11 12
11 11 12 13
11 12 13 14 15 16 17 1 19 1
11 12 13 14 15 16 17 18 1 19 1
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
