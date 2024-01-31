#!/web/cs2041/bin/python3.7.2
import asyncio, codecs, datetime, getpass, glob, multiprocessing, os, paramiko, random, re, subprocess, sys, tempfile, threading, time

activity_directory = os.path.dirname(os.path.realpath(sys.argv[0]))
sys.path.append(activity_directory)
import subprocess_with_resource_limits
import numpy as np
import cryptography, warnings
warnings.simplefilter("ignore", cryptography.utils.CryptographyDeprecationWarning)
# YUK
binary = './run_farnarkle_ai'
autotest = os.path.join(activity_directory, '..', '..', 'scripts', 'autotest')
assert os.path.exists(autotest)
autotest_command = [autotest, 'farnarkle_ai', '-l', 'farnarkle_ai_0']
run_farnarkle_ai_source = "{}/solutions/run_farnarkle_ai.c".format(activity_directory)
compile_command = "dcc -O -Dmain=_main edited_farnarkle.c edited_run_farnarkle_ai.c -o run_farnarkle_ai".format(activity_directory).split()
not_competing_file = 'not_competing'
farnarkle_tournament_data_directory = '/home/cs1511/public_html/19T2/farnarkle_tournament/'
round_complete_file = ".round_complete"
hidden_tiles_file = ".hidden_tiles"


MAX_TILE = 8
N_TILES = 4


def run(*args, **kwargs):
    (stdout, stderr, returncode) = subprocess_with_resource_limits.run(*args, **kwargs)
    stdout = codecs.decode(stdout, 'ascii', errors='replace')
    stderr = codecs.decode(stderr, 'ascii', errors='replace')
    return (stdout, stderr, returncode)

lab_capacity = {'piano' : 18, 'organ' : 20, 'clavier' : 21, 'viola' : 18,'cello' : 18, 'bugle' : 18, 'horn' : 17, 'sitar' : 25, 'kora' : 24, 'flute' : 25, 'oboe' : 25, 'drum' : 24, 'bongo' : 20, 'tabla' : 25, 'lyre' : 19, 'oud' : 19}
lab_capacity = {'piano' : 18, 'organ' : 20, 'clavier' : 21, 'viola' : 18,'cello' : 18, 'bugle' : 18, 'horn' : 17, 'sitar' : 25, 'kora' : 24, 'flute' : 25, 'oboe' : 25, 'drum' : 24, 'bongo' : 20, 'tabla' : 25, 'oud' : 19}
lab_machines = ['%s%02d' % (lab, int(n)) for (lab,capacity) in lab_capacity.items() for n in range(0, capacity)]

ssh_command = "ssh -x -oStrictHostKeyChecking=no -oForwardX11=no -oForwardX11Trusted=no -oForwardAgent=no".split()
ping_command = "ping -c 1 -q".split()
uptime_command = "uptime".split()
machine_busy_if_load_average_above = 0.10
debug = 0

def run_command_machine(hostname, command, username = getpass.getuser(), stdin='', fallback_to_local_execution=False, use_paramiko=True):
    if debug > 1: print('run_command_machine', hostname, command, file=sys.stderr)
    if not use_paramiko:
        with tempfile.TemporaryFile(dir='.') as stdin_stream:
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
            if debug > 1: print(exit_status_ssh, file=sys.stderr)
            stdout = stdout_ssh.read().decode()
            stderr = stderr_ssh.read().decode()
            if 'Input/output error' in stderr:
                raise ValueError("bad host")
            if 'Failed to import the site module' in stderr:
                raise ValueError("bad host")
            client.close()
        except Exception as e:
            if fallback_to_local_execution:
                with tempfile.TemporaryFile(dir='.') as stdin_stream:
                    stdin_stream.write(stdin.encode())
                    stdin_stream.seek(0)
                    p = subprocess.run(command, shell=True, stdin=stdin_stream, stdout=subprocess.PIPE, stderr=subprocess.PIPE,universal_newlines=True)
                return (p.stdout, p.stderr, p.returncode)
            else:
                if debug: print(run_command_machine, hostname,e, file=sys.stderr)
                return ('', '', 2)
        return (stdout, stderr, exit_status_ssh)

def ping(machine):
    (stdout,stderr,returncode) = run(ping_command + [machine], max_wall_clock=15, debug=debug)
    if debug and returncode != 0:
        print(machine, 'ping failed', file=sys.stderr)
    return returncode == 0

def find_submissions(work_directory):
    submissions = []
    for root, dirs, files in os.walk(work_directory):
        for name in files:
            if name == 'submission.tar':
                submissions.append(root)
    return submissions

def run_submission(submission_dir, n_tiles, max_tile, hidden_tiles):
    os.chdir(submission_dir)
    zid = os.path.basename(submission_dir.rstrip('/\\'))
    if not os.path.exists('submission.tar'):
        return (-1, [], 0, 'no submission')
    submission_time = os.path.getmtime('submission.tar')
    compile_not_needed = False
    if os.path.exists(binary) and os.path.getmtime(binary) > submission_time:
        # with random N_TILES, MAX_TILE assume compile needed
        # compile_not_needed = True
        pass
    elif os.path.exists(not_competing_file):
        if submission_time > os.path.getmtime(not_competing_file):
            os.unlink(not_competing_file)
        else:
            with open(not_competing_file) as f:
                return (-1, zid, submission_time, f.read())
    if not compile_not_needed:
        (stdout, stderr, returncode) = run(['tar', '-f', 'submission.tar', '-x'], debug=debug)
        if returncode != 0:
            return (-1, zid, submission_time, 'tar error: ' + stdout + stderr) # shouldn't happen
        (stdout, stderr, returncode) = run(autotest_command, debug=debug)
        if returncode != 0:
            with open(not_competing_file, 'w') as f:
                print(stdout + stderr, file=f)
            return (-1, zid, submission_time, 'autotest error:' + stdout + stderr)
        edit_parameters("farnarkle.c", n_tiles, max_tile, "edited_farnarkle.c")
        edit_parameters(run_farnarkle_ai_source, n_tiles, max_tile, "edited_run_farnarkle_ai.c")
        (stdout, stderr, returncode) = run(compile_command, debug=debug)
        if returncode != 0:
            return (-1, zid, submission_time, 'compile error:' + stdout + stderr) # shouldn't happen
    (stdout, stderr, returncode) = run([binary], input=" ".join(hidden_tiles), max_cpu=180,max_wall_clock=900,  debug=debug)
    if returncode != 0:
        return (0, zid, submission_time, 'tournament error: ' + stdout + stderr)
    m = re.search('(\d+) turns to guess the', stdout)
    if m:
        return (int(m.group(1)), zid, submission_time, stdout + stderr)
    else:
        return (0, zid, submission_time, 'tournament internal error: ' + stdout + stderr)

def edit_parameters(in_file, n_tiles, max_tile, out_file):
    with open(in_file) as f:
        contents = f.read()
    contents = re.sub('^\s*#\s*define\s+N_TILES\s.*', '#define N_TILES ' + n_tiles, contents, flags=re.MULTILINE)
    contents = re.sub('^\s*#\s*define\s+MAX_TILE\s.*', '#define MAX_TILE ' + max_tile, contents, flags=re.MULTILINE)
    with open(out_file, "w") as f:
        f.write(contents)

def get_hidden_tiles_round_directory(rounds_directory):
    pathname = os.path.join(rounds_directory, hidden_tiles_file)
    try:
        with open(pathname) as f:
            tiles = f.read().split()
            n_tiles = tiles.pop(0)
            max_tile = tiles.pop(0)
            if len(tiles) == int(n_tiles):
                return n_tiles, max_tile, tiles
            else:
                print("Invalid hidden tiles file", pathname)
    except (OSError, ValueError):
        pass
    n_tiles_mean, n_tiles_variance = 4.0, 1
    n_tiles = np.random.normal(n_tiles_mean, n_tiles_variance)
    n_tiles = max(n_tiles, n_tiles_mean/2)
    n_tiles = min(n_tiles, n_tiles_mean*2)
    n_tiles = int(round(n_tiles))
    max_tile_mean, max_tile_variance = 8.0, 2
    max_tile = np.random.normal(max_tile_mean, max_tile_variance)
    max_tile = max(max_tile, max_tile_mean/2)
    max_tile = min(max_tile, max_tile_mean*2)
    max_tile = int(round(max_tile))
    hidden_tiles = list(map(str, [1 + random.randrange(max_tile) for i in range(n_tiles)]))
    with open(pathname, "w") as f:
        print(n_tiles, max_tile, " ".join(hidden_tiles), file=f)
    return str(n_tiles), str(max_tile), hidden_tiles

def get_next_round_directory(rounds_directory):
    if not os.path.exists(rounds_directory):
        os.mkdir(rounds_directory)
        os.chmod(rounds_directory, 0o775)
    round_subdirs = sorted(glob.glob(os.path.join(rounds_directory,'*[0-9]')))
    if debug:
        print('round_subdirs', round_subdirs)
    if round_subdirs and not os.path.exists(os.path.join(round_subdirs[-1], round_complete_file)):
        return round_subdirs[-1]
    if round_subdirs:
        last_round_number = int(os.path.basename(round_subdirs[-1]))
    else:
        last_round_number = -1
    new_round_subdir = os.path.join(rounds_directory, "%08d"% (last_round_number + 1))
    if debug:
        print('creating:', new_round_subdir)
    os.mkdir(new_round_subdir)
    os.chmod(new_round_subdir, 0o775)
    return new_round_subdir

def run_submission_to_file(submission_dir, output_file, n_tiles, max_tile, hidden_tiles):
    if os.path.exists(output_file) and os.stat(output_file).st_size:
        return (0,  0, 0, '')
    result = run_submission(submission_dir, n_tiles, max_tile, hidden_tiles)
    with open(output_file, "w") as f:
        print(" ".join(map(str, result)), file=f)
        print('N_TILES was', n_tiles, 'MAX_TILE was', max_tile, 'hidden_tiles were', ' '.join(hidden_tiles), file=f)
    os.chmod(output_file, 0o664)
    print(" ".join(map(str, result)))

def run_submission_to_file_worker(args):
    (submission_dir, lab_machine, n_tiles, max_tile, hidden_tiles, round_directory) = args
    zid = os.path.basename(submission_dir)
    output_file = os.path.join(round_directory, zid)
    submission_file = os.path.join(submission_dir, 'submission.tar')
    if not os.path.exists(submission_file):
        return
    submission_time = os.path.getmtime(submission_file)
    not_competing = os.path.join(submission_dir, 'not_competing_file')
    if os.path.exists(not_competing):
        if submission_time > os.path.getmtime(not_competing_file):
            os.unlink(not_competing_file)
        else:
            with open(not_competing_file, "r") as f:
                cached = f.read()
            result = (-1, zid, None, submission_time, cached)
            with open(output_file, "w") as f:
                f.write(" ".join(map(str, result)), file=f)
            return (-1, lab_machine, cached, '')
    command = ' '.join([os.path.realpath(sys.argv[0]), submission_dir, output_file, n_tiles, max_tile] + hidden_tiles)
    (stdout,stderr,returncode) = run_command_machine(lab_machine, command)
    if debug:
        print(lab_machine,stdout,stderr,returncode)
    if returncode != 0:
        print('non-zero return code:', lab_machine, command, stdout,stderr, returncode, file=sys.stderr)
    return (returncode == 0, lab_machine,stdout,stderr)

def unordered_timeout(function, iterable, n_workers=16, timeout=15):
    pool = multiprocessing.Pool(n_workers)
    results = []
    def alarm(timeout_list):
        if debug: print('timeout',  timeout, file=sys.stderr)
        timeout_list.append(timeout)
    timeout_list = []
    timer = threading.Timer(timeout, alarm, args=[timeout_list])
    timer.start()
    async_results = []
    for i in iterable:
        if timeout_list:
            break
        a = pool.apply_async(function, [i], callback=lambda r: results.append(r))
        async_results.append(a)
    for a in async_results:
        if timeout_list:
            break
        a.wait(1)
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
            if debug:
                print(machine, 'load:', m.group(1), file=sys.stderr)
                sys.stderr.flush()
            return float(m.group(1))


def machine_load_worker(machine):
    return (machine, machine_load(machine))

def lab_machines_sorted_by_load(n_workers=16, timeout=15):
    results = unordered_timeout(machine_load_worker, lab_machines, n_workers=n_workers, timeout=timeout)
    return [t[0] for t in sorted(r for r in results if r[0] is not None)]

if __name__ == '__main__':
    os.nice(15)
    if sys.argv[3:]:
        run_submission_to_file(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5:])
        sys.exit(0)
    n_workers = int(sys.argv[1]) if sys.argv[1:] else 16
    pool = multiprocessing.Pool(n_workers)
    while True:
        start_time = time.time()
        worker_hostnames = lab_machines_sorted_by_load(n_workers=n_workers, timeout=42)
        print(len(worker_hostnames), 'hosts available')
        round_directory = get_next_round_directory(farnarkle_tournament_data_directory)
        n_tiles, max_tile, hidden_tiles = get_hidden_tiles_round_directory(round_directory)
        print(round_directory, n_tiles, max_tile,  hidden_tiles)
        submissions = find_submissions('/home/cs1511/19T2.work/lab06_farnarkle_ai/')
        jobs = [(submission_dir, lab_machine, n_tiles, max_tile, hidden_tiles, round_directory) for (submission_dir, lab_machine) in zip(submissions, worker_hostnames*16)]
        n_failures = 0
        for result in pool.imap_unordered(run_submission_to_file_worker, jobs):
            if debug:
                print(result)
            if not result[0]:
                print('failure:', '\n'.join(map(str, result)))
                n_failures += 1
        if not n_failures:
            with open(os.path.join(round_directory, round_complete_file),"w") as f:
                print(datetime.datetime.now(), file=f)
            finish_time = time.time()
            time_delta = finish_time - start_time
            if time_delta < 60:
                time.sleep(60 - time_delta)
    try:
        asyncio.get_event_loop().close()
    except Exception:
        pass
