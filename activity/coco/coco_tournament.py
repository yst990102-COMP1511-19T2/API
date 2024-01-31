#!/home/cs2041/bin/python3.7.2 -B

import collections, datetime, gc, getpass, glob, multiprocessing, os, paramiko, pickle, random, re, subprocess, sys, tempfile, threading, time
import cryptography, warnings
warnings.simplefilter("ignore", cryptography.utils.CryptographyDeprecationWarning)
try:
    import asyncio
    import uvloop
    asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())
except ImportError as e:
    print(e)

QUALIFICATION_DIRECTORY = "/web/cs1511/19T2/work/ass1_coco/qualified/"
QUALIFICATION_DIRECTORY = "/web/cs1511/19T2/work/ass1_coco/binaries/"
TOURNAMENT_DIRECTORY = "/web/cs1511/19T2/coco_tournament/"
TOURNAMENT_DIRECTORY = "/web/cs1511/19T2/coco_marking_tournament/"
ROUND_COMPLETE_FILE = ".round_complete"
N_PLAYERS = 4

lab_capacity = {'piano' : 18, 'organ' : 20, 'clavier' : 21, 'viola' : 18,'cello' : 18, 'bugle' : 18, 'horn' : 17, 'sitar' : 25, 'kora' : 24, 'flute' : 25, 'oboe' : 25, 'drum' : 24, 'bongo' : 20, 'tabla' : 25, 'lyre' : 19, 'oud' : 19}
lab_capacity = {'viola' : 18,'cello' : 18, 'bugle' : 18, 'horn' : 17, 'sitar' : 25, 'kora' : 24, 'flute' : 25, 'oboe' : 25, 'drum' : 24, 'bongo' : 20, 'tabla' : 25, 'lyre' : 19}
lab_capacity = {'viola' : 18,'cello' : 18, 'bugle' : 18, 'horn' : 17, 'sitar' : 25, 'kora' : 24, 'flute' : 25, 'oboe' : 25, 'drum' : 24, 'bongo' : 20, 'tabla' : 25}
lab_machines = ['%s%02d' % (lab, int(n)) for (lab,capacity) in lab_capacity.items() for n in range(0, capacity)]
lab_machines = set(lab_machines) - set(''.split())

ssh_command = "ssh -x -oStrictHostKeyChecking=no -oForwardX11=no -oForwardX11Trusted=no -oForwardAgent=no".split()

debug = 1
#game_command = [os.path.join(config['variables'].scripts_directory, 'coco_referee'), '--tournament']
game_command = ['/home/cs1511/bin/coco_referee', '--tournament']

def main():
    while True:
       t = time.localtime()
       if t.tm_wday < 5 and t.tm_hour > 8 and t.tm_hour < 20:
           run_rounds(n_workers = 64, n_simultaneous_rounds=32 )
       else:
           run_rounds(n_workers = 200, n_simultaneous_rounds=50)
       gc.collect() # speculative

def run_rounds(n_workers = 128, n_simultaneous_rounds=32):
    worker_hostnames = lab_machines_sorted_by_load(n_workers=n_workers, timeout=42)
    print(len(worker_hostnames), 'hosts available')
    round_directories = get_next_n_round_directories(n=n_simultaneous_rounds)
    print(round_directories)
    for round_directory in round_directories:
        for f in os.listdir(round_directory):
            try:
                os.unlink(os.path.join(round_directory, f))
            except OSError:
                pass
    players = get_players()
    scores = None
    round_games = {}
    completed_round_games = {}
    remote_game_details = {}
    for round_directory in round_directories:
        round_games[round_directory] = games = group_players(players, scores)
        completed_round_games[round_directory] = []
        seed = random.getrandbits(24)
        for (i, game_zids) in enumerate(games):
            hostname = worker_hostnames[i % len(worker_hostnames)]
            binaries = [os.path.join(QUALIFICATION_DIRECTORY, zid) for zid in game_zids]
            remote_game_details[tuple(game_zids)] = (game_zids, hostname, seed, binaries, round_directory)

    round_scores = collections.defaultdict(lambda: {})
    player_names = collections.defaultdict(lambda: {})
    attempts = 0
    while remote_game_details and attempts < 3:
#       results = unordered_timeout(run_game_worker, remote_game_details.values(), n_workers=n_workers, timeout=1200)
        with  multiprocessing.Pool(n_workers) as pool:
            results = pool.imap_unordered(run_game_worker,  list(remote_game_details.values()))
            for finished_game in results:
                if process_finished_game(finished_game, round_games, completed_round_games, player_names, round_scores):
                    game_zids = finished_game[0][0]
                    del remote_game_details[tuple(game_zids)]
        attempts += 1
    for v in remote_game_details.items():
        print('error: failed game', v)
    if debug > 1:
        for round_directory in round_directories:
            zids = round_scores[round_directory].keys()
            round_details = [(round_scores[round_directory][z], z, player_names[round_directory][z]) for z in zids]
            for (score, zid, player_name) in sorted(round_details, reverse=True):
                print(score, zid, player_name, file=sys.stderr)

def process_finished_game(finished_game, round_games, completed_round_games, player_names, round_scores):
    (zids, hostname, seed, binaries, round_directory) = finished_game[0]
    (stdout, stderr, returncode) = finished_game[1]
    if not extract_scores(stdout, player_names[round_directory], round_scores[round_directory]):
        if debug:
            print('Could not extract scores', round_directory, zids)
            return None
    pathname = os.path.join(round_directory, '_'.join(zids)+'.txt')
    with open(pathname, "w") as f:
        print(clean_referee_stdout(stdout), file=f, end='')
    completed_round_games[round_directory].append(zids)
    completed_games = len(completed_round_games[round_directory])
    total_games = len(round_games[round_directory])
    if debug:
        print(round_directory, completed_games, 'of', total_games, 'completed')
    if completed_games == total_games:
        with open(os.path.join(round_directory, "scores.pkl"), "wb") as f:
            pickle.dump(round_scores[round_directory], f)
        with open(os.path.join(round_directory, "player_names.pkl"), "wb") as f:
            pickle.dump(player_names[round_directory], f)
        with open(os.path.join(round_directory, ROUND_COMPLETE_FILE),"w") as f:
            print(datetime.datetime.now(), file=f)
    return finished_game

def run_game_remote(args):
    (zids, hostname, seed, binaries, round_directory) = args
    command = game_command + ['-s', str(seed)] + binaries
    if debug > 1:
        print(' '.join(command), file=sys.stderr)
#   p = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
#   return (p.stdout, p.stderr,p.returncode)
    return run_command_machine(hostname, ' '.join(command), use_paramiko=True, fallback_to_local_execution=True)

def run_game_worker(args):
    return (args, run_game_remote(args))


def clean_referee_stdout(referee_stdout):
    referee_stdout = re.sub(r' \([^\(]*\d{7}\)', '', referee_stdout)
    return referee_stdout

def extract_scores(referee_stdout, player_names, scores):
    finishing_positions = re.findall(r'^#(\d) with \d+ penalty points (.*) \(([^\(]*)\)\s*$', referee_stdout, re.MULTILINE)
    if len(finishing_positions) != 4:
        return False
    finishers = collections.defaultdict(list)
    for (position, name, binary) in finishing_positions:
        finishers[position].append((position, name, binary))
    tournament_points = [3,2,1]
    for tied_players in finishers.values():
        n_tied = len(tied_players)
        points = sum(tournament_points[0:n_tied])/n_tied
        tournament_points = tournament_points[n_tied:]
        for (position, name, binary) in tied_players:
            m = re.search(r'(\d{7})$', binary)
            if m:
                zid = m.group(1)
                player_names[zid] = name
                scores[zid] = points
    return True

def group_players(players, scores):
    random.shuffle(players)
    return [sorted(players[n:n+N_PLAYERS]) for n in range(0, len(players), N_PLAYERS)]

def get_next_round_directory(tournament_directory=TOURNAMENT_DIRECTORY):
    if not os.path.exists(tournament_directory):
        os.mkdir(tournament_directory)
        os.chmod(tournament_directory, 0o775)
    round_subdirs = sorted(glob.glob(os.path.join(tournament_directory,'*[0-9]')))
    if debug > 1:
        print('round_subdirs', round_subdirs, file=sys.stderr)
    if round_subdirs and not os.path.exists(os.path.join(round_subdirs[-1], ROUND_COMPLETE_FILE)):
        return round_subdirs[-1]
    if round_subdirs:
        last_round_number = int(os.path.basename(round_subdirs[-1]))
    else:
        last_round_number = -1
    new_round_subdir = os.path.join(tournament_directory, "%08d"% (last_round_number + 1))
    if debug:
        print('creating:', new_round_subdir, file=sys.stderr)
    os.mkdir(new_round_subdir)
    os.chmod(new_round_subdir, 0o775)
    return new_round_subdir


def get_next_n_round_directories(tournament_directory=TOURNAMENT_DIRECTORY, n=3):
    if not os.path.exists(tournament_directory):
        os.mkdir(tournament_directory)
        os.chmod(tournament_directory, 0o775)
    round_subdirs = sorted(glob.glob(os.path.join(tournament_directory,'*[0-9]')))
    if debug > 1:
        print('round_subdirs', round_subdirs, file=sys.stderr)
    next_n_round_directories = []
    for dir in round_subdirs[-n:]:
        if not os.path.exists(os.path.join(dir, ROUND_COMPLETE_FILE)):
            next_n_round_directories.append(dir)
    if round_subdirs:
        last_round_number = int(os.path.basename(round_subdirs[-1]))
    else:
        last_round_number = -1
    for i in range(n):
        if len(next_n_round_directories) == n:
            break
        new_round_subdir = os.path.join(tournament_directory, "%08d"% (last_round_number + 1 +i))
        if debug:
            print('creating:', new_round_subdir, file=sys.stderr)
        os.mkdir(new_round_subdir)
        os.chmod(new_round_subdir, 0o775)
        next_n_round_directories.append(new_round_subdir)
    return next_n_round_directories

def get_players(directory=QUALIFICATION_DIRECTORY):
    return [p for p in os.listdir(directory) if re.match(r'^\d{7}$', p)]


def run_command_machine(hostname, command, username = getpass.getuser(), stdin='', fallback_to_local_execution=False, use_paramiko=True):
    if debug > 1: print('run_command_machine', hostname, command, file=sys.stderr)
    if not use_paramiko:
        with tempfile.TemporaryFile() as stdin_stream:
            stdin_stream.write(stdin.encode())
            stdin_stream.seek(0)
            p = subprocess.run(ssh_command + [hostname, command], stdin=stdin_stream, stdout=subprocess.PIPE, stderr=subprocess.PIPE,universal_newlines=True)
        return (p.stdout, p.stderr, p.returncode)
    else:
        try:
            client = paramiko.SSHClient()
            client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            client.connect(hostname, username=username, allow_agent=False, look_for_keys=False, timeout=60, banner_timeout=60, key_filename='/home/'+username+'/.ssh/id_rsa')
            stdin_ssh,stdout_ssh,stderr_ssh = client.exec_command(command, timeout=180)
            if stdin:
                stdin_ssh.write(stdin.encode())
            stdin_ssh.flush()
            # https://stackoverflow.com/questions/8052840/paramiko-piping-blocks-forever-on-read
            stdin_ssh.channel.shutdown_write()
            stdin_ssh.close()
            exit_status_ssh = stdout_ssh.channel.recv_exit_status() # waits for command to terminate
            if debug > 1: print('run_command_machine', hostname, command, 'exit_status', exit_status_ssh, file=sys.stderr)
            stdout = stdout_ssh.read().decode()
            stderr = stderr_ssh.read().decode()
            if 'Input/output error' in stderr:
                raise ValueError("bad host")
            if 'Failed to import the site module' in stderr:
                raise ValueError("bad host")
            client.close()
        except Exception as e:
            if fallback_to_local_execution:
#                if hostname != 'login':
#                    return run_command_machine('login', command, username, stdin, fallback_to_local_execution, use_paramiko=True)
                if debug: print('run_command_machine falling back to local execution', hostname, e, file=sys.stderr)
                with tempfile.TemporaryFile() as stdin_stream:
                    stdin_stream.write(stdin.encode())
                    stdin_stream.seek(0)
                    p = subprocess.run(command, shell=True, stdin=stdin_stream, stdout=subprocess.PIPE, stderr=subprocess.PIPE,universal_newlines=True)
                return (p.stdout, p.stderr, p.returncode)
            else:
                if debug: print('run_command_machine failed', hostname,e, file=sys.stderr)
                return ('', '', 2)
        return (stdout, stderr, exit_status_ssh)


def unordered_timeout(function, jobs, n_workers=16, timeout=15):
    pool = multiprocessing.Pool(n_workers)
    def alarm(timeout_list):
        if debug: print('timeout',  timeout, file=sys.stderr)
        timeout_list.append(timeout)
    timeout_list = []
    timer = threading.Timer(timeout, alarm, args=[timeout_list])
    timer.start()
    results = []
    async_results = []
    for i in jobs:
        if timeout_list:
            break
        a = pool.apply_async(function, [i])
        async_results.append(a)
    while async_results:
        unfinished = []
        for a in async_results:
            try:
                results.append(a.get(1))
            except multiprocessing.TimeoutError:
                unfinished.append(a)
        async_results = unfinished
        if timeout_list:
            break
    timer.cancel()
    try:
        pool.terminate()
    except AssertionError:
        pass
    return results

def machine_load(machine):
    (stdout, stderr, exit_status) = run_command_machine(machine, 'uptime', use_paramiko=True)
    if exit_status == 0:
        m = re.search(r'load\s+average:\s+(\d*\.?\d*)', stdout, flags=re.I)
        if m:
            if debug > 1:
                print(machine, 'load:', m.group(1), file=sys.stderr)
                sys.stderr.flush()
            return float(m.group(1))


def machine_load_worker(machine):
    return (machine_load(machine), machine)

def lab_machines_sorted_by_load(n_workers=16, timeout=15):
    results = unordered_timeout(machine_load_worker, lab_machines, n_workers=n_workers, timeout=timeout)
    return [t[1] for t in sorted(r for r in results if r[0] is not None and r[0] < 0.5)]

if __name__ == '__main__':
    os.nice(10)
    main()
