#!/usr/bin/python3
tests = """
max_cpu=10
ignore_case=True
ignore_white_space=True
compare_only_characters="0123456789"
no_reproduce_command=1

files=list_intersection_size.c
compiler_args=-Dmain=_main list_intersection_size.c test_list_intersection_size.c -o test_list_intersection_size
command=./test_list_intersection_size

pre_compile_command="../check_arrays_not_used.sh list_intersection_size.c;../check_at_most_one_call_malloc.sh list_intersection_size.c"
pre_compile_command_shell=1

-
1142 - 1142
2242 - 2243
342 -
- 343
421 422 423 -
421 422 423 - 421
421 422 423 - 421 422
421 422 423 - 423 422
421 422 423 - 421 423
421 422 423 - 421 422 423
423 422 421 - 423 422 421
421 424 429 422 - 421 422 423 425 428
421 424 425 429 422 - 421 423 425 428 422
421 424 425 429 422 - 423 425 428 422
421 422 423 424 425 426 427 428 - 424 426 428 422 421 423
8 - 4 6 8 2 1 3
7 8 - 4 6 8 2 1 3
6 7 8 - 4 6 8 2 1 3
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    print('{0} command=./test_list_intersection_size {1} description="./list_intersection_size {1}"'.format(test_number, t))
    test_number += 1
