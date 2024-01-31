#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=list_get_middle.c
compiler_args=-Dmain=_main list_get_middle.c test_list_get_middle.c -o test_list_get_middle
command=./test_list_get_middle

pre_compile_command="../check_arrays_not_used.sh list_get_middle.c;../check_at_most_one_call_malloc.sh list_get_middle.c"
pre_compile_command_shell=1

3 1 4 1 5 9
3 4 5 9
1 2
42
1 2 3 4 5 6 7 8 9 10
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_list_get_middle {1} description="./list_get_middle {1}"'.format(test_number, t))
    test_number += 1
