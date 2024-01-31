#!/usr/bin/python3
tests = """
max_cpu=3
no_reproduce_command=1

files=list_intersection_size.c
compiler_args=-Dmain=_main list_intersection_size.c test_list_intersection_size.c -o test_list_intersection_size
command=./test_list_intersection_size

pre_compile_command="./check_arrays_not_used.sh list_intersection_size.c;./check_at_most_one_call_malloc.sh list_intersection_size.c"
pre_compile_command_shell=1

-
42 - 42
42 - 43
42 -
- 43
1 2 3 -
1 2 3 - 1
1 2 3 - 1 2
1 2 3 - 3 2
1 2 3 - 1 3
1 2 3 - 1 2 3
3 2 1 - 3 2 1
1 4 5 9 2 - 1 2 3 5 8
1 4 5 9 2 - 1 3 5 8 2
1 4 5 9 2 - 3 5 8 2
1 2 3 4 5 6 7 8 - 4 6 8 2 1 3
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    print('{0} command=./test_list_intersection_size {1} description="./list_intersection_size {1}"'.format(test_number, t))
    test_number += 1
