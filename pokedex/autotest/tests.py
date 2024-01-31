#!/usr/bin/python3
dir = '/home/cs1511/public_html/19T1/activities/pokedex/'
tests = f"""

# build by
# cd /home/cs1511/public_html/19T1/private/activities/pokedex
# /home/cs1511/public_html/19T1/private/scripts/autotest_update_from_solution
# git commit autotest -m 'updated autotest'
# git push

# Initial autotest using main.c

max_cpu=3
files=pokedex.c
pre_compile_command="cp {dir}pokedex.h {dir}main.c {dir}pokemon.[ch] {dir}different_pokemon.[ch] ."
pre_compile_command_shell=1
checkers="1511 c_check --ban-non-char-arrays --ban-string-library"
compiler_args=pokedex.c pokemon.c main.c -o pokedex
command="./pokedex"

a 7 Squirtle 0.5 9 water None
d

a 143 snorlax  2.1 460.0 normal none
p

a 7 Squirtle 0.5 9 water None
d
p
a 143 snorlax  2.1 460.0 normal none
d
p

a 75 graveler 1.0 105.0 ground rock
d
f
d

a 95 onix 8.8 210.0 ground rock
p
f
p

a 6 Squirtle 0.5 9 water None
a 2 Ivysaur 1 13 grass poison
d
p
f
d
p

a 6 Squirtle 0.5 9 water None
p
d
a 7 Bulbasaur 0.7 6.9 poison grass
p
d
a 2 Ivysaur 1 13 grass poison
p
d

p

a 1 Bulbasaur 0.7 6.9 poison grass
d
a 143 snorlax  2.1 460.0 normal none
d
>
d

a 6 Squirtle 0.5 9 water None
p
d
a 67 Bulbasaur 0.7 6.9 poison grass
>
p
d
a 2 Ivysaur 1 13 grass poison
>
p
d

a 53 persian 1.0 32.0 normal none
a 54 psyduck 0.8 19.6 water none
a 55 golduck 1.7 76.6 water none
a 59 arcanine 1.9 155.0 fire none
a 60 poliwag 0.6 12.4 water none
a 56 mankey 0.5 28.0 fighting none
a 57 primeape 1.0 32.0 fighting none
a 58 growlithe 0.7 19.0 fire none
d
>
d
>
>
d
>
>
>
d

a 6 Squirtle 0.5 9 water None
d
>
d
a 7 Bulbasaur 0.7 6.9 poison grass
d
a 2 Ivysaur 1 13 grass poison
d
>
d

a 143 snorlax  2.1 460.0 normal none
a 1 Bulbasaur 0.7 6.9 poison grass
d
>
d
<
d

a 92 gastly 1.3 0.1 poison ghost
a 93 haunter 1.6 0.1 poison ghost
a 90 shellder 0.3 4.0 water none
a 91 cloyster 1.5 132.5 ice water
a 94 gengar 1.5 40.5 poison ghost
<
d
>
>
d
>
>
d
>
>
d
<
<
<
<
d
<
<
<
d

a 1 Bulbasaur 0.7 6.9 poison grass
a 141 snorlax  2.1 460.0 normal none
a 7 Bulbasaur 0.7 6.9 poison grass
f
d
p
>
d
p
f
d
p
>
d
p
f
d
p

a 58 growlithe 0.7 19.0 fire none
a 59 arcanine 1.9 155.0 fire none
a 54 psyduck 0.8 19.6 water none
a 55 golduck 1.7 76.6 water none
a 56 mankey 0.5 28.0 fighting none
a 57 primeape 1.0 32.0 fighting none
a 60 poliwag 0.6 12.4 water none
a 61 poliwhirl 1.0 20.0 water none
a 62 poliwrath 1.3 54.0 fighting water
g
>
g
>
g
>
g
>
>
g

a 54 psyduck 0.8 19.6 water none
g
d
a 55 golduck 1.7 76.6 water none
g
d
>
a 56 mankey 0.5 28.0 fighting none
g
d
>
p

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison
a 21 Spearow 0.3 2.0 flying normal
a 42 Golbat 1.6 55.0 flying poison
f
>
<
f
>
f
<
d
>
>
f
d
>
p
<
<
<
p

compiler_args=pokedex.c different_pokemon.c main.c -o pokedex

a 42 Testle 0.5 9 Steel Test_Type
f
d
p

>
<

compiler_args=pokedex.c pokemon.c main.c -o pokedex
compilers="dcc:dcc --valgrind --leak-check"

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison
r
p

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison
r
p
r
p
r
p

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison
a 21 Spearow 0.3 2.0 flying normal
a 42 Golbat 1.6 55.0 flying poison
f
m 2
r
p
m 42
r
p
m 6
r
p

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison
a 21 Spearow 0.3 2.0 flying normal
a 42 Golbat 1.6 55.0 flying poison
m 2
d
p
m 6
d
p
m 42
d
p

a 6 Squirtle 0.5 9 water None
c
t
a 7 Bulbasaur 0.7 6.9 poison grass
c
t
a 2 Ivysaur 1 13 grass poison
f
c
t

c
t

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison
e 6 7
n
s
e 7 2
n
s

a 6 Squirtle 0.5 9 water None
a 7 Bulbasaur 0.7 6.9 poison grass
a 2 Ivysaur 1 13 grass poison
e 6 7
n
s
e 7 2
n
s
e 6 2
n
s

a 100 voltorb 0.5 10.4 electric none
a 101 electrode 1.2 66.6 electric none
a 102 exeggcute 0.4 2.5 psychic grass
a 103 exeggutor 2.0 120.0 psychic grass
a 104 cubone 0.4 6.5 ground none
a 105 marowak 1.0 45.0 ground none
a 106 hitmonlee 1.5 49.8 fighting none
a 107 hitmonchan 1.4 50.2 fighting none
a 108 lickitung 1.2 65.5 normal none
a 109 koffing 0.6 1.0 poison none
a 110 weezing 1.2 9.5 poison none
n
s
e 100 110
n
s
e 101 107
e 104 106
s
e 106 101
e 110 104
n
s
>
n
s
q

a 100 voltorb 0.5 10.4 electric none
a 101 electrode 1.2 66.6 electric none
a 102 exeggcute 0.4 2.5 psychic grass
f
>
f
S e
p

a 100 voltorb 0.5 10.4 electric none
a 101 electrode 1.2 66.6 electric none
a 102 exeggcute 0.4 2.5 psychic grass
>
f
>
F
p
q
q

a 100 voltorb 0.5 10.4 electric none
a 101 electrode 1.2 66.6 electric none
a 102 exeggcute 0.4 2.5 psychic grass
>
f
>
T electric
p
q
q

a 103 exeggutor 2.0 120.0 psychic grass
a 117 seadra 1.2 25.0 water none
f
>
f
S ra
p
q
S e
p
q
q

a 101 electrode 1.2 66.6 electric none
a 102 exeggcute 0.4 2.5 psychic grass
a 100 voltorb 0.5 10.4 electric none
f
>
f
>
f
F
p
q
q

a 101 electrode 1.2 66.6 electric none
a 102 exeggcute 0.4 2.5 psychic grass
a 103 exeggutor 2.0 120.0 psychic grass
a 104 cubone 0.4 6.5 ground none
a 105 marowak 1.0 45.0 ground none
a 106 hitmonlee 1.5 49.8 fighting none
a 107 hitmonchan 1.4 50.2 fighting none
a 108 lickitung 1.2 65.5 normal none
a 109 koffing 0.6 1.0 poison none
a 110 weezing 1.2 9.5 poison none
a 111 rhyhorn 1.0 115.0 rock ground
a 112 rhydon 1.9 120.0 rock ground
a 113 chansey 1.1 34.6 normal none
a 114 tangela 1.0 35.0 grass none
a 115 kangaskhan 2.2 80.0 normal none
a 116 horsea 0.4 8.0 water none
a 117 seadra 1.2 25.0 water none
a 118 goldeen 0.6 15.0 water none
a 119 seaking 1.3 39.0 water none
a 120 staryu 0.8 34.5 water none
a 121 starmie 1.1 80.0 psychic water
a 122 mr-mime 1.3 54.5 fairy psychic
a 123 scyther 1.5 56.0 flying bug
a 124 jynx 1.4 40.6 psychic ice
a 125 electabuzz 1.1 30.0 electric none
a 126 magmar 1.3 44.5 fire none
a 127 pinsir 1.5 55.0 bug none
a 128 tauros 1.4 88.4 normal none
a 129 magikarp 0.9 10.0 water none
a 130 gyarados 6.5 235.0 flying water
>
>
f
>
f
>
>
f
>
f
>
>
f
>
f
>
>
f
>
f
>
>
f
>
f
>
>
f
>
f
F
p
q
T water
p
q
T psychic
p
q
S a
p
q
S zz
p
q
q


a 138 Omanyte 0.4 7.5 water rock
a 139 Omastar 1.0 35.0 water rock
a 140 Kabuto 0.5 11.5 water rock
a 141 Kabutops 1.3 40.5 water rock
a 142 Aerodactyl 1.8 59.0 flying rock
a 44 Gloom 0.8 8.6 poison grass
f
>
f
>
f
>
f
>
f
>
f
S oM
p
q
q

"""

level_commands = {
    1 : "apdf",
    2: "><mrgq",
    3: "xct",
    4: "esn",
    5: "FST"
}
command_level = {}
for (level, commands) in level_commands.items():
    for command in commands:
        command_level[command] = level

leak_check = False
test_number = 1
input = []
for  t in tests.splitlines() + ['']:
    t = t.strip()
    if t and '=' not in t and '#' not in t:
        input.append(t)
        continue
    if input:
        stdin = '\\n'.join(input) + '\\n'
        description = ' '.join(i[0] for i in input if i)
        level = max(command_level.get(i[0], 1) for i in input  if i)
        if leak_check:
            level = max(level, 2)
        print(f'{test_number} description="Level {level} - {description}" stdin="{stdin}"')
        test_number += 1
        input = []
    if 'leak' in t:
        leak_check = True
    print(t)
