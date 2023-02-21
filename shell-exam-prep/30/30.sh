#!/bin/bash

[ $# -eq 1 ] || exit 1

LOGDIR=$1

find $LOGDIR -maxdepth 3 -mindepth 2 -type d -printf "%f\n" | sort | uniq | while read -r friend; do
	
echo $friend "$(find $LOGDIR -type f -printf "%p\n" | grep -E ".*$friend/.{23}$" | xargs wc -l | tail -n1 | awk -F ' ' '{print $1}')"
	
done | sort -r -n -k2,2 | head -n 10 
