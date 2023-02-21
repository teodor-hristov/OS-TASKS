#!/bin/bash

[ $# -eq 3 ] && [ -e $1 ] || exit 1
FILE=$1
KEY1=$2
KEY2=$3

cat $FILE | while read line; do
	VAL="$(echo $line | awk -F '=' '{print $2}')"
        KEYS="$(echo $line | awk -F '=' '{print $1}')"
	if [ $KEYS = $KEY2 ]; then
		echo $KEY2 "=" "$(echo $VAL | tr -d "$(cat $FILE | awk -F '=' '$1 == "'$KEY1'" {print $2}' | tr -d ' ')")"
		continue 
	fi
	echo $line
done 
