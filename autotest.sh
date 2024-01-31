#!/bin/bash

# config.sh只适用于vlab机器上，根目录有备份，这里需要注释掉
# config_file="$(dirname "$(readlink -f "$0")")"/config.sh

# work_dir="$(dirname "${ASSIGNDIR}")"
# work_dir_name="$(basename "${work_dir}")"
# unsw_session="${work_dir_name%.work}"
# course_account="$(basename "$(dirname "${work_dir}")")"

# base_dir="/web/${course_account}/${unsw_session}"

# # handling  being run by give from dryrun
# test ! -r "$config_file" &&
# 	config_file="./1511_config.sh"

# test -r "$config_file" &&
# 	. "$config_file"

autotest="/home/yst990102/COMP1511/autotest/autotest.py"
test -f "$autotest" || {
	echo "Internal error can not find find autotest script"
	exit 1
}

parameters="
	default_compilers = {'c': [['dcc', '-Werror']]}
"

# if ASSIGNDIR is set, assume we are being run as give's dryrun script and create !dryrun_record
if test -z "$ASSIGNDIR"; then
	python3 -I "$autotest" --exercise_directory "/home/yst990102/COMP1511/API/activity" --parameters "$parameters" "$@"
else
	python3 -I -u "$autotest" --exercise_directory "/home/yst990102/COMP1511/API/activity" --parameters "$parameters" "$@" |
		tee '!dryrun_record'
fi
