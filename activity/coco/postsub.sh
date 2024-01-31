#!/bin/bash -p
coco_directory=$(dirname $(readlink -f $0))
scripts_directory=$coco_directory/../../scripts/

$scripts_directory/postsub_git "$@"

tarfile="$1"
submission_dir=$(dirname "$tarfile")

if egrep '^0 tests passed' "$submission_dir/!dryrun_record" >/dev/null
then
    echo "!!! Your code did not pass the submission check."
    echo "!!! Your submission will not be included in the tournament."
    echo "!!! Fix the errors and submit again to join the tournament."
    exit
fi

echo -n "Would you like to enter the Coco tournament (yes/no)? "
read answer
case "$answer" in
[Yy]*)  $coco_directory/tournament_qualification.sh "$@" ;;
*)  echo "Submission not entered" ;;
esac
