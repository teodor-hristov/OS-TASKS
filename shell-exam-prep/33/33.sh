#!/bin/bash

DATA="$(cat - | while read line; do
if [ -n "$(echo $line | grep -E "^([0-9]|-[1-9])+$")" ]; then
		echo $line
	fi
done | sort -n -r | uniq)" 
MAX="$(echo $DATA | cut -d " " -f1)"
echo $DATA | grep -E -o "[-]{,1}$MAX"

for u in  $DATA; do
	if [ $u -ge 0 ]; then
		continue
	fi

	tmp=$u
	sum=
	while [ 1 ];do
		sum=$((tmp%10+sum))
		tmp=$((tmp/10))		
		if [ $tmp -le 0 ];then
			echo $u $sum
			break
		fi
	done

done | sort -n -k2,2 | head -n 1 | cut -d " " -f1 
