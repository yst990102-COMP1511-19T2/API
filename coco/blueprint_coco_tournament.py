#!/usr/bin/python3

import glob, os, pickle,  re
from collections import defaultdict
from flask import Blueprint, abort, g, redirect, session
from utility import render_template_with_variables, authentication_page_needed, get_student_names

app = Blueprint('coco_tournament', __name__)

TOURNAMENT_DIRECTORY = "/web/cs1511/19T2/coco_tournament/"
ROUND_COMPLETE_FILE = ".round_complete"
N_PLAYERS = 4
MIN_ROUNDS_COUNTED = 5
MAX_ROUNDS_COUNTED = 2000
debug = 0


@app.route("/coco_tournament/me", methods=['GET', 'POST'])
@app.route("/coco_tournament/me/", methods=['GET', 'POST'])
def me():
    g.no_cache = True
    authentication_page = authentication_page_needed()
    if authentication_page:
        return authentication_page
    if session['zid'] == '9300162':
        session['zid'] = '5242579'
    return redirect('coco_tournament/' + session['zid'])

@app.route("/coco_tournament/<regex(r'\d{7}'):zid>", methods=['GET', 'POST'])
@app.route("/coco_tournament/<regex(r'\d{7}'):zid>/", methods=['GET', 'POST'])
def rounds(zid):
    g.no_cache = True
    if not g.is_tutor:
        authentication_page = authentication_page_needed()
        if authentication_page:
            return authentication_page
        # just ignore supplied zid if not tutor
        zid = session['zid']
    rounds = []
    for round_directory in sorted(glob.glob(os.path.join(TOURNAMENT_DIRECTORY,'*[0-9]')), reverse=True):
        if not os.path.exists(os.path.join(round_directory, ROUND_COMPLETE_FILE)):
            continue
        with open(os.path.join(round_directory, 'scores.pkl'), 'rb') as f:
            scores = pickle.load(f)
        if zid not in scores:
            continue
        round_full_name = os.path.basename(round_directory)
        round_short_name = re.sub(r'^$', '0', round_full_name.lstrip('0'))
        rounds.append((scores[zid], round_full_name, round_short_name))
    return render_template_with_variables('templates/coco_tournament_rounds.html', **{
        'min_rounds_counted' : MIN_ROUNDS_COUNTED,
        'max_rounds_counted' : MAX_ROUNDS_COUNTED,
        'zid' : zid,
        'rounds' : rounds,
        })

@app.route("/coco_tournament/<regex(r'\d{7}'):zid>/<regex(r'\d+'):round>", methods=['GET', 'POST'])
def round_output(zid, round):
    g.no_cache = True
    if not g.is_tutor:
        authentication_page = authentication_page_needed()
        if authentication_page:
            return authentication_page
        # just ignore supplied zid if not tutor
        zid = session['zid']
    output_files = glob.glob(os.path.join(TOURNAMENT_DIRECTORY, round, '*'+zid+'*'))
    if not output_files:
        abort(404)
    game_file = output_files[0]
    try:
        with open(game_file) as f:
            raw_output = f.read()
    except OSError:
        abort(404)
    return render_template_with_variables('templates/coco_tournament_round_output.html', **{
        'min_rounds_counted' : MIN_ROUNDS_COUNTED,
        'max_rounds_counted' : MAX_ROUNDS_COUNTED,
        'zid' : zid,
        'round' : re.sub(r'^$', '0', round.lstrip('0')),
        'raw_output' : raw_output,
        })

@app.route('/coco_tournament/', methods=['GET', 'POST'], defaults={'rounds': str(MAX_ROUNDS_COUNTED)})
@app.route("/coco_tournament/rounds/<rounds>", methods=['GET', 'POST'])
def leaderboard(rounds):
#    g.no_cache = True
    max_rounds_counted = MAX_ROUNDS_COUNTED
    try:
        max_rounds_counted = int(rounds)
    except ValueError:
        pass
    max_rounds_counted = max(max_rounds_counted, MIN_ROUNDS_COUNTED)
    max_rounds_counted = min(max_rounds_counted, 10 * MAX_ROUNDS_COUNTED)
    scores, player_names, last_round_number = get_results(max_rounds=max_rounds_counted)
    average_scores = defaultdict(list)
    unofficial_scores = defaultdict(list)
    student_names = get_student_names()
    for (zid,zid_scores) in scores.items():
        if len(zid_scores) >= MIN_ROUNDS_COUNTED:
            average = sum(zid_scores)/len(zid_scores)
            if zid in student_names:
                average_scores[average] += [(zid,zid_scores)]
            else:
                unofficial_scores[average] += [(zid,zid_scores)]
#   student_details = {}
#   with open("/web/teachadmin/data/student_names", encoding="latin-1") as f:
#       for line in f:
#           (course,zid,name,program_stage,session,gender,email,aliases) = line.strip().split("|")
#           student_details[zid] = (zid, name,program_stage,gender)
    table_rows = []

    # add the non-students in separately -- doesn't need to be sorted bc ranks are irrelevant
    for (average, zids) in unofficial_scores.items():
        for (zid, zid_scores) in sorted(zids):
#           name = zid
#           if zid in student_details:
#               name = student_details[zid][1]
#               m =re.match(r'(.*?), (\S+)', name)
#               if m:
#                   name = m.group(2) + ' ' + m.group(1)
#               name += " (unofficial)"
            player_name = player_names.get(zid, '?') + " (unofficial)"
            table_rows.append((-1, average, len(zid_scores), player_name))

    position = 1
    for (average,zids) in sorted(average_scores.items(), reverse=True):
        for (zid,zid_scores) in sorted(zids):
#           name = zid
#           if zid in student_details:
#               name = student_details[zid][1]
#               m =re.match(r'(.*?), (\S+)', name)
#               if m:
#                   name = m.group(2) + ' ' + m.group(1)
            player_name = player_names.get(zid, '?')
            table_rows.append((position, average, len(zid_scores), player_name))
        position += len(zids)
    # because the tutors were added separately, need to sort the table rows
    table_rows.sort(key=lambda r: r[1], reverse=True)

    return render_template_with_variables('templates/coco_tournament.html', **{
        'min_rounds_counted' : MIN_ROUNDS_COUNTED,
        'max_rounds_counted' : max_rounds_counted,
        'table_rows' : table_rows,
        'last_round_number' : last_round_number,
        })

def get_results(rounds_directory=TOURNAMENT_DIRECTORY, max_rounds=MAX_ROUNDS_COUNTED):
    i = 0
    scores = defaultdict(list)
    existing_player_names = {}
    player_names = {}
    last_round_number = 0
    for round_directory in sorted(glob.glob(os.path.join(rounds_directory,'*[0-9]')), reverse=True):
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
        with open(os.path.join(round_directory, 'player_names.pkl'), 'rb') as f:
            player_names = pickle.load(f)
        player_names.update(existing_player_names)
        existing_player_names = player_names
        i = i + 1
        if i >= max_rounds:
            break
    return scores, player_names, last_round_number
