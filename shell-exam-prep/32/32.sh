#!/bin/bash

[ $# -eq 2 ] || exit 1
IN=$1
OUT=$2
echo "" >> $OUT
cat $IN | while read -r line; do
	TOSEARCH="$(echo $line | cut -d "," -f2,3,4)"
	if [ -z "$(cat $OUT | grep -E "$TOSEARCH")" ]; then
		echo "$(cat $IN | grep -E "$TOSEARCH" | sort -n -k1,1 | head -n 1)" >> $OUT

	fi
done
