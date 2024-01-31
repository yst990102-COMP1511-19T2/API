#!/bin/sh
# run as a cron job on williams to ensure farnarkle tournament is running
# 0 * *  *  * /home/cs1511/public_html/19T2/private/activities/farnarkle_ai/run_farnarkle_tournament.sh

. $(dirname $(readlink -f $0))/../../scripts/config.sh
cd $public_html_session_directory|| exit
pkill -u $course_account -f run_farnarkle_tournament.py
sleep 10
pkill -u $course_account --signal 9 -f run_farnarkle_tournament.py
rm -f $WORK/lab06_farnarkle_ai/*/*/not_competing
# has to be run from private repo because it uses solutions code
setsid private/scripts/run_farnarkle_tournament.py >>farnarkle_tournament.log 2>&1 </dev/null &
