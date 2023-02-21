#!/bin/bash

[ $# -eq 2 ] || exit 1

FILE1=$1
FILE2=$2

[ -e $FILE1 ] && [ -e $FILE2 ] || exit 1

if [ "$(cat $FILE1 | wc -l)" -ge "$(cat $FILE2 | wc -l)" ]; then
	cat $FILE1 | awk -F '-' '{print $2" - "$3"\n"}' 1> isong1
else
	cat $FILE2 | awk -F '-' '{print $2" - "$3"\n"}' 1> isong2
fi
