#!/usr/bin/python3
tests = """
max_cpu=10
no_reproduce_command=1

files=most_frequent_list.c
compiler_args=-Dmain=_main most_frequent_list.c test_most_frequent_list.c -o test_most_frequent_list
command=./test_most_frequent_list

pre_compile_command="./check_arrays_not_used.sh most_frequent_list.c;./check_at_most_one_call_malloc.sh most_frequent_list.c"
pre_compile_command_shell=1

655 10 204 8192 76 38 204 43912 204
5 4 6 5 4 6
3 5 7 11 13 15 3 17 19 23 29 13 3
1 100 1000 10000 100000 100000 100000 10000 1000 10 1
100000 99999 9999 999 99 9 9 999 100000 9999
1
1 1
1 1 1 1
1 2 1 2 1 2
10 100 1000 11 101 1001 1000 1001 100 10 1
1 2 3 4 5
7 6 1 2 2 4 2 1 7 4 1 6 2 5 7 1 1 7 5 3 7 5 3 6 3 6
3 7 4 4 1 5 4 1 7 7 4 2 3 4 6 7 4 3 4 1 5 4 6 2 2 2 7 5 7 4 6 4 7 6 2 7 3 7 2 2 7 2 6 4 4 2 1 4 7 5 5 7 3 2 4 3 4 2 7 5 2 2 1 7 5 5 7 6 1 2 1 2 3 7 7 3 5 6 4 4 7 2 7 2 1 6 2 7 3 6 3 2 1 1 4 5 6 2 4 4
1 1 4 2 3 1 5

"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    if t == "NULL":
        t = ""
    print('{0} command=./test_most_frequent_list {1} description="./most_frequent_list {1}"'.format(test_number, t))
    test_number += 1
