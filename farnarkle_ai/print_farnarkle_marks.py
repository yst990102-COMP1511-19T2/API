#!/usr/bin/python3

# print_farnarkle_marks.py|tee /home/cs1511/public_html/19T2/work/lab06_farnarkle_ai/marks.tx
import glob, os, re
from collections import defaultdict

farnarkle_tournament_data_directory = "../../../farnarkle_tournament/"
round_complete_file = ".round_complete"
min_rounds_counted = 5
max_rounds_counted = 1000
debug = 0

MAX_TILE = 8
N_TILES = 4

def get_results(rounds_directory=farnarkle_tournament_data_directory, max_rounds=max_rounds_counted):
    i = 0
    scores = defaultdict(list)
    for round_directory in sorted(glob.glob(os.path.join(rounds_directory,'*[0-9]')), reverse=True):
        if not os.path.exists(os.path.join(round_directory, round_complete_file)):
            if debug > 1:
                print('incomplete round', round_directory)
            continue
        for output_file in glob.glob(os.path.join(round_directory,'*[0-9]')):
            with open(output_file) as f:
                m = re.match('^(\d+)', f.readline())
                if m:
                    if debug:
                        print(output_file, m.group(1))
                    score = int(m.group(1))
                    if score > 0:
                        if debug > 1:
                            print(os.path.basename(output_file), m.group(1))
                        scores[os.path.basename(output_file)] += [int(m.group(1))]
                    elif score == 0:
                        scores[os.path.basename(output_file)] += [MAX_TILE*N_TILES]
        i = i + 1
        if i >= max_rounds:
            break
    return scores

if __name__ == '__main__':
    scores = get_results()
    for (zid, scores) in scores.items():
        average = sum(scores)/len(scores)
        mark = 0.5 + (30 - average) / 40.0
        mark = min(1, mark)
        print(zid, "%.3f"%mark)
