#!/usr/bin/python3

function_name = 'array_maximum'

tests = f"""
max_cpu=10
no_reproduce_command=1

files={function_name}.c
compiler_args=-Dmain=_main {function_name}.c test_{function_name}.c -o {function_name}

1 2 3 4 5
3 14 15 9 2 6 5
1 2 4 8 16 32 64 128 256 512
10 8 6 4 2
1 2 3 2 1
1
100 200 100
50 100 50 100


"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    elements = t.split()
    element_list = ", ".join(elements)
    print(f'{test_number} command=./{function_name} {t} description="{function_name}({len(elements)}, {{{element_list}}})"')
    test_number += 1
