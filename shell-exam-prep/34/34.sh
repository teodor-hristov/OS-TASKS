#!/bin/bash

while [ $# -gt 0 ]; do
	parse=0
	N=10

	if [ "-n" = $1 ]; then
		shift 1
		parse=1
	fi
	if [ $parse ]; then
		parse=0
		N=$1
		shift 1
	fi

	file=$1	
	identifier="$(echo $1 | head -c-5)"
	shift 1
	cat $file | while read -r line; do
		
		echo $line | cut -d ":" -f1,2,3 | awk -F ' ' '{print $1" "$2" ""'$identifier'"" ""'$(echo $line | cut -d ":" -f)'"}'	

	done	
done
