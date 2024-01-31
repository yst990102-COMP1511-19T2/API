#!/usr/bin/python3
tests = """

max_cpu=3
files=vector_distance.c
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=./vector_distance

3 6 0 1  2 7 1 2
42 43 44 42 42  42 43 44 42 42
20  10
1 2 3  3 2 1
1 2 3 5 7 11  31 29 23 19 17 13

3 6 0 1  1 0 6 3
41 41 42 43 44 42 42  41 41 42 43 44 42 42
20000  10000
1 2 3 4 5 6 7 8 9   9 8 7 6 5 4 3 2 1
1 2 3 5 7 11 13 15 17 19  59 57 53 47 43 41 37 31 23 29


"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    numbers = t.split()
    assert(len(numbers) % 2 == 0)
    n = len(numbers)//2
    stdin = str(n) + '\\n'
    stdin += ' '.join(numbers[0:n]) + '\\n'
    stdin += ' '.join(numbers[n:]) + '\\n'
    print(f'{test_number} stdin="{stdin}" description="{n}  {t}"')
    test_number += 1
