#!/bin/bash -p
coco_directory=$(dirname $(readlink -f $0))
scripts_directory=$coco_directory/../../scripts/
. $scripts_directory/config.sh
#set -x

tarfile="$1"
submission_dir=$(dirname "$tarfile")
zid=$(basename "$submission_dir")

rm -rf "$submission_dir/qualification/"
mkdir -p "$submission_dir/qualification" || exit 1
tar -C "$submission_dir/qualification" -xf "$tarfile" || exit 1
cd "$submission_dir/qualification" || exit 1
dcc coco.c -o $zid || exit
dcc --valgrind coco.c -o $zid-valgrind || exit
mkdir -p ../../../qualified/
mv $zid  $zid-valgrind  ../../../qualified/

echo "Player should appear in next round of tournament at $canonical_url/coco_tournament/"