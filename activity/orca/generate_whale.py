#!/usr/bin/python3
import datetime, random, sys

all_whales ="""
Sei whale
Bryde's whale
Pygmy right whale
Blue whale
Antarctic minke whale
Humpback whale
Dwarf minke whale
Fin whale
Southern right whale
Long-finned pilot whale
Pygmy sperm whale
Short-finned pilot whale
Dwarf sperm whale
Melon-headed whale
Gray's beaked whale
Rough-toothed dolphin
Andrews' beaked whale
Indo-Pacific humpbacked dolphin
True's beaked whale
Dusky dolphin
Ginkgo-toothed beaked whale
Hourglass dolphin
Cuvier's beaked whale
Risso's dolphin
Hector's beaked whale
Coastal bottlenose dolphin
Shepherd's beaked whale
Pantropical spotted dolphin
Arnoux's beaked whale
Spinner dolphin
Longman's beaked whale
Striped dolphin
Blainville's beaked whale
Common dolphin
Strap-toothed beaked whale
Fraser's dolphin
Southern bottlenose whale
Southern right whale dolphin
Orca
Australian snubfin dolphin
Pygmy killer whale
Spectacled porpoise
False killer whale
Bottlenose dolphin
"""

common_whales ="""
Sei whale
Bryde's whale
Pygmy right whale
Blue whale
Humpback whale
Dwarf minke whale
Fin whale
Southern right whale
Long-finned pilot whale
Pygmy sperm whale
Short-finned pilot whale
Dwarf sperm whale
Indo-Pacific humpbacked dolphin
Coastal bottlenose dolphin
Spinner dolphin
Striped dolphin
Common dolphin
Orca
"""

common_whale_list = [s.strip() for s in common_whales.strip().splitlines()]
all_whale_list = [s.strip() for s in all_whales.strip().splitlines()]

now = datetime.datetime.now()
one_year_ago = now - datetime.timedelta(days=365)
now = int(now.timestamp())
one_year_ago = int(one_year_ago.timestamp())


for i in range(int(sys.argv[1])):
    d = random.randrange(one_year_ago, now)
    when = datetime.date.fromtimestamp(d).strftime("%d/%m/%y")
    how_many = random.randrange(1, 42)
    species = random.choice(all_whale_list)
    print(when, "%2d" % how_many, species)
