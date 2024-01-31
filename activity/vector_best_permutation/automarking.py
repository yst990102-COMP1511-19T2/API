#!/usr/bin/python3
tests = """

max_cpu=40
files=vector_best_permutation.c
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=./vector_best_permutation

6 8 15 11  42 43 17 3
18 16 19 11 42 32  77 64 11 99 21 42
34 56 42 44 35 38 39 50 62 61 58 43 45 32 33 48 46 52 63 57 55 37 53 49 59 41 51 47 40 54 60 36  23 30 13 16 14 33 25 41 15 32 35 26 28 40 31 38 39 11 19 21 37 18 27 12 36 17 24 34 22 20 10 29

34 45 12 17  5 3 1 9
1 2 3 4 5 6  6 5 4 3 2 1
20 3 32 12 33 24 11 16 39 9 13 2 26 18 8 40 34 10 38 7 25 36 17 6 30 22 15 19 37 21 1 35 23 41 5 31 4 29 28 27 14  13 40 3 39 26 35 5 12 10 36 24 22 42 2 38 27 4 9 8 21 7 29 11 6 41 18 30 14 16 32 34 37 15 20 33 17 28 31 25 23 19
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
