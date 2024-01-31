#!/usr/bin/python3
tests = """

max_cpu=3
ignore_case=1
ignore_white_space=1

percentage 5 10
percentage 10 1
percentage 5 2
percentage 1 1
percentage 100 5
percentage 0 20

"""
import collections
test_count = collections.defaultdict(int)
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    stdin = ""
    list_elements = []
    stdin_words = t.strip().split()
    program = stdin_words.pop(0)
    stdin = '\\n'.join(stdin_words) + '\\n'
    description = ' '.join(stdin_words)
    print('{}_{} command="./{}" stdin="{}" description="{}"'.format(program, test_count[program], program, stdin, description))
    test_count[program] += 1
