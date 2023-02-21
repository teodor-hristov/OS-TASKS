#!/bin/bash

[ $# -eq 2 ] || ( echo "Parameters" && exit 1 )

A=$1
B=$2

find ./ -maxdepth 1 -type f | while read file; do

	if [ "$(cat $file | wc -l)" -le $A ]; then
		echo "move to a"
	elif [ "$(cat $file | wc -l)" -ge $A ] &&  [ "$(cat $file | wc -l)" -le $B ]; then 
		echo "move to b"
	else
		echo "move to c"
	fi
done
