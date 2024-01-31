#!/usr/bin/python3
tests = """
max_cpu=3
no_reproduce_command=1
files=list_insert_head.c
compiler_args=-Dmain=_main list_insert_head.c test_list_insert_head.c -o test_list_insert_head
command=./test_list_insert_head

pre_compile_command="./check_arrays_not_used.sh list_insert_head.c"
pre_compile_command_shell=1

10
10 46
10 46 47
12 16 7 8 12 13 19 21 12
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
