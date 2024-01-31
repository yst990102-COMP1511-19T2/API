#!/bin/bash
# run as a cron job on zappa to ensure coco tournament is running
# * * *  *  * /home/cs1511/public_html/19T2/private/activities/coco/run_coco_tournament.sh

ulimit -u 2000
ulimit -n 2048
. $(dirname $(readlink -f $0))/../../scripts/config.sh
cd $public_html_session_directory|| exit

#test -z "$1" &&  test -d coco_tournament && (($(date +%s) - $(stat  -c %Y coco_tournament) < 1800)) && exit 0
test -z "$1" &&  test -d coco_marking_tournament && (($(date +%s) - $(stat  -c %Y coco_marking_tournament) < 1800)) && exit 0

pkill -u $course_account -f coco_tournament.py
sleep 10
pkill -u $course_account --signal 9 -f coco_tournament.py
#test `hostname` = zappa && exit

# has to be run from private repo because it uses solutions code
setsid private/activities/coco/coco_tournament.py >>coco_marking_tournament.log 2>&1 </dev/null &
