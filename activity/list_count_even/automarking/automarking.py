#!/usr/bin/python3
tests = """
max_cpu=10
ignore_case=True
ignore_white_space=True
compare_only_characters="0123456789"
no_reproduce_command=1

files=count_even_list.c
compiler_args=-Dmain=_main count_even_list.c test_count_even_list.c -o test_count_even_list
command=./test_count_even_list

pre_compile_command="./check_arrays_not_used.sh count_even_list.c;./check_at_most_one_call_malloc.sh count_even_list.c"
pre_compile_command_shell=1

5 8 9 7 9 3 2 3 8 4
3 5 7 9 11 13 15
6 5 6 7
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 8
4 3 1 3 7 9
30 18 5 52 50 7 23 60 14 61
68 32 76 93 7 85 62 29 77 29
30 91 89 19 11 23 98 68 32 47
84 84 5 13 22 28 50 88 90 85
3 3 2 2 3 3 4 4
96 40 33 80 56 34 45 23 7 73 28 78 76 66 16 72 68 13 7 30 64 67 48 7 74 63 78 68 27 9 42 34
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
