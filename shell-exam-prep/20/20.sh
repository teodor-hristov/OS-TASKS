#!/bin/bash

[ $# -eq 1 ] || exit 1

FILE=$1
[ -e $FILE ] || exit 1

I=0
cat $FILE | awk -F '-' 'NF > 1 {print NR". "$2" "$3}' | sort -k2,2 | while read u; do
	echo $u
	I=$(($I+1))
done > out
