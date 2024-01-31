#!/usr/bin/python3
tests = """

max_cpu=3
files=vector_permutation.c
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=./vector_permutation

42 43 44 45  3 1 2 0
40 41 42 43 44 45  0 1 2 3 4 5
40 41 42 43 44 45  5 4 3 2 1 0
1024 0
48 36 48 24 12  4 3 1 0 2
48 36 48 24 12  4 3 5 0 2
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
