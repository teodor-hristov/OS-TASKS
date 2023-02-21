#!/bin/bash

[ $# -eq 1 ] || exit 1
[ $(whoami) = "root" ] || exit 1

GIVENRSS=$1
ps -e -o uid,pid,rss | tail -n+2 | while read -r line; do
	LINERSS="$(echo $line | awk -F ' ' '{print $3"\n"}')"		
	if [ $LINERSS -ge $GIVENRSS ]; then
		kill $(echo $line | awk -F ' ' '{print $2}')
	fi
	LINERSS=""
done
