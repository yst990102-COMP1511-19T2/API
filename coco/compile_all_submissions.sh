#!/bin/bash
coco_directory=$(dirname $(readlink -f $0))
scripts_directory=$coco_directory/../../scripts/
. $scripts_directory/config.sh
submission_dir=$WORK/ass1_coco
binaries_dir=$submission_dir/binaries/
mkdir -p $binaries_dir
temp_dir=`mktemp -d /tmp/compile_all_submissions.XXXXXXXXXX` || exit 1
trap 'rm -fr $temp_dir' EXIT INT TERM
cd $temp_dir || exit 1

for tar_file in $submission_dir/*-*/[0-9]*[0-9]/submission.tar
do
    zid=$(basename $(dirname $tar_file))
    rm -f * 2>/dev/null
    tar  -xf "$tar_file" || continue
    dcc coco.c -o $zid >/dev/null 2>&1 || continue
    dcc --valgrind coco.c -o $zid-valgrind >/dev/null 2>&1 || continue
    mv $zid  $zid-valgrind  $binaries_dir
done
