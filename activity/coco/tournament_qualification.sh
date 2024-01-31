#!/bin/bash -p
coco_directory=$(dirname $(readlink -f $0))
scripts_directory=$coco_directory/../../scripts/

$scripts_directory/ssh.py /home/cs1511/.ssh/id_rsa cs1511@login $coco_directory/tournament_qualification1.sh "$@"
