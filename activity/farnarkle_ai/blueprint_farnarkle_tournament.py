#!/usr/bin/python3

import glob, os, re
from collections import defaultdict
from flask import Blueprint, abort, g, redirect, session
from utility import render_template_with_variables, authentication_page_needed, get_student_names

app = Blueprint('farnarkle_tournament', __name__)

farnarkle_tournament_data_directory = "../farnarkle_tournament/"
round_complete_file = ".round_complete"
min_rounds_counted = 5
max_rounds_counted = 1000
debug = 0

MAX_TILE = 8
N_TILES = 4

AWESOME_TUTORS = ["3424700", "5165457", "5164335"]

@app.route("/farnarkle_tournament/me", methods=['GET', 'POST'])
@app.route("/farnarkle_tournament/me/", methods=['GET', 'POST'])
def me():
    g.no_cache = True
    authentication_page = authentication_page_needed()
    if authentication_page:
        return authentication_page
    if session['zid'] == '9300162':
        session['zid'] = '5215420'
    return redirect('farnarkle_tournament/' + session['zid'])

@app.route("/farnarkle_tournament/<regex(r'\d{7}'):zid>", methods=['GET', 'POST'])
@app.route("/farnarkle_tournament/<regex(r'\d{7}'):zid>/", methods=['GET', 'POST'])
def rounds(zid):
    g.no_cache = True
    if not g.is_tutor:
        authentication_page = authentication_page_needed()
        if authentication_page:
            return authentication_page
        # just ignore supplied zid if not tutor
        zid = session['zid']
    rounds = []
    for round_directory in sorted(glob.glob(os.path.join(farnarkle_tournament_data_directory,'*[0-9]')), reverse=True):
        if not os.path.exists(os.path.join(round_directory, round_complete_file)):
            continue
        output_file = os.path.join(round_directory, zid)
        if not os.path.exists(output_file):
            continue
        round_score = ''
        with open(output_file) as f:
            m = re.match('^(\d+)', f.readline())
            if m:
                score = int(m.group(1))
                if score > 0:
                    round_score = str(score)
        round_full_name = os.path.basename(round_directory)
        round_short_name = re.sub(r'^$', '0', round_full_name.lstrip('0'))
        rounds.append((round_score, round_full_name, round_short_name))
    return render_template_with_variables('templates/farnarkle_tournament_rounds.html', **{
        'min_rounds_counted' : min_rounds_counted,
        'max_rounds_counted' : max_rounds_counted,
        'zid' : zid,
        'rounds' : rounds,
        })

@app.route("/farnarkle_tournament/<regex(r'\d{7}'):zid>/<regex(r'\d+'):round>", methods=['GET', 'POST'])
def round_output(zid, round):
    g.no_cache = True
    if not g.is_tutor:
        authentication_page = authentication_page_needed()
        if authentication_page:
            return authentication_page
        # just ignore supplied zid if not tutor
        zid = session['zid']
    try:
        with open(os.path.join(farnarkle_tournament_data_directory, round, zid)) as f:
            raw_output = f.read()
    except OSError:
        abort(404)
    return render_template_with_variables('templates/farnarkle_tournament_round_output.html', **{
        'min_rounds_counted' : min_rounds_counted,
        'max_rounds_counted' : max_rounds_counted,
        'zid' : zid,
        'round' : re.sub(r'^$', '0', round.lstrip('0')),
        'raw_output' : re.sub(r'^.*?Turn', 'Turn', raw_output),
        })

@app.route('/farnarkle_tournament/', methods=['GET', 'POST'], defaults={'path': ''})
@app.route('/farnarkle_tournament/<path>', methods=['GET', 'POST'])
def catchall_url(path):
    g.no_cache = True
    scores = get_results()
    average_scores = defaultdict(list)
    unofficial_scores = defaultdict(list)
    student_names = get_student_names()
    for (zid,zid_scores) in scores.items():
        if len(zid_scores) >= min_rounds_counted:
            average = sum(zid_scores)/len(zid_scores)
            if zid in student_names:
                average_scores[average] += [(zid,zid_scores)]
            else:
                unofficial_scores[average] += [(zid,zid_scores)]
    student_details = {}
    with open("/web/teachadmin/data/student_names", encoding="latin-1") as f:
        for line in f:
            (course,zid,name,program_stage,session,gender,email,aliases) = line.strip().split("|")
            student_details[zid] = (zid, name,program_stage,gender)
    table_rows = []

    # add the tutors in separately -- doesn't need to be sorted bc ranks are irrelevant
    for (average, zids) in unofficial_scores.items():
        for (zid, zid_scores) in sorted(zids):
            name = zid
            if zid in student_details:
                name = student_details[zid][1]
                m =re.match(r'(.*?), (\S+)', name)
                if m:
                    name = m.group(2) + ' ' + m.group(1)
                name += " (unofficial)"
            table_rows.append((-1, average, len(zid_scores), name))

    for (position, (average,zids)) in enumerate(sorted(average_scores.items())):
        for (zid,zid_scores) in sorted(zids):
            name = zid
            if zid in student_details:
                name = student_details[zid][1]
                m =re.match(r'(.*?), (\S+)', name)
                if m:
                    name = m.group(2) + ' ' + m.group(1)

            table_rows.append((position+1, average, len(zid_scores), name))

    # because the tutors were added separately, need to sort the table rows
    table_rows.sort(key=lambda r: r[1])

    return render_template_with_variables('templates/farnarkle_tournament.html', **{
        'min_rounds_counted' : min_rounds_counted,
        'max_rounds_counted' : max_rounds_counted,
        'table_rows' : table_rows,
        })

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
