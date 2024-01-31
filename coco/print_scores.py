#!/usr/bin/python3
import glob, os, pickle,  re
from collections import defaultdict

TOURNAMENT_DIRECTORY = "/web/cs1511/19T2/coco_tournament.pre_submission/"
ROUND_COMPLETE_FILE = ".round_complete"
debug = 1

def piece_wise_linear(x, mapping):
    if isinstance(mapping, dict):
        mapping = mapping.items()
    mapping = sorted(mapping)
    x0, mapped_x0 = mapping.pop(0)
    if x < x0:
        return mapped_x0
    while mapping:
        x1, mapped_x1 = mapping.pop(0)
        if x <= x1:
            return mapped_x0 + (x - x0)/(x1 - x0) * (mapped_x1 - mapped_x0)
        x0, mapped_x0 = x1, mapped_x1
    return mapped_x0


def main():
    scores = defaultdict(list)
    existing_player_names = {}
    player_names = {}
    last_round_number = 0
    for round_directory in sorted(glob.glob(os.path.join(TOURNAMENT_DIRECTORY,'*[0-9]')), reverse=True):
        if not os.path.exists(os.path.join(round_directory, ROUND_COMPLETE_FILE)):
            if debug > 1:
                print('incomplete round', round_directory)
            continue
        if not last_round_number:
            last_round_number = os.path.basename(round_directory)
        with open(os.path.join(round_directory, 'scores.pkl'), 'rb') as f:
            round_scores = pickle.load(f)
        for (zid,score) in round_scores.items():
            scores[zid].append(score)
        player_names.update(existing_player_names)
        existing_player_names = player_names
    for zid in scores:
        s = scores[zid]
        score = sum(s)/len(s)
        mark = piece_wise_linear(score, {2.10 : 100, 1.95:85, 1.35:75, 1.1:60, 0.5:55, 0:40})
        mark = min(100, mark)
        mark = 0.8 * mark
        print("%s %.1f %.4f %d" % (zid, mark, score, len(s)))

if __name__ == "__main__":
    main()