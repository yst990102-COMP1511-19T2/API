#!/usr/bin/python3
tests = """

max_cpu=20
files=vector_best_permutation.c
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=./vector_best_permutation

6 8 15 11  42 43 17 3
18 16 19 11 42 32  77 64 11 99 21 42
34 56 42 44 35 38 39 50 62 61 58 43 45 32 33 48 46 52 63 57 55 37 53 49 59 41 51 47 40 54 60 36  23 30 13 16 14 33 25 41 15 32 35 26 28 40 31 38 39 11 19 21 37 18 27 12 36 17 24 34 22 20 10 29
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
