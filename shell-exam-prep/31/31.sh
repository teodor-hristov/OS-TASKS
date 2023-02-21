#!/bin/bash

[ $# -eq 2 ] || exit 1
DIR=$2
FILE=$1
[ -f $FILE ] || exit 1
[ -d $DIR ] || exit 1
cnt=0
cat $FILE | awk -F ':' '{print $1}' | awk -F ' ' '{print $1" "$2}' | sort | uniq | while read -r name;do
	PHRASE="$(cat $FILE | grep -E "^$name.*" | awk -F ':' '{print $2"\n"}')"
	echo $PHRASE > $DIR"/"$cnt".txt"
	echo $name";"$cnt >> "dict.txt"
	cnt=$((cnt+1))
done
