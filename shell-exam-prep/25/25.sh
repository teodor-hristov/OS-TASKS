#!/bin/bash

[ "$(whoami)" = "tedo3637" ] && [ $# -eq 3 ] || exit 1

SRC=$1
DST=$2
SUB=$3

echo "$(find $SRC -type f 2>/dev/null)" | while read file; do
	if [ -n "$(basename "$file" | grep -E ".*$SUB.*")" ]; then
		cp --parent $file $DST
	fi
done


