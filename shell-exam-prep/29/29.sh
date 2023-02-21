#!/bin/bash

cat /etc/passwd | awk -F ':' '{print $1" "$6}' | while read -r usr;do
	USER="$(echo $usr | cut -d " " -f1)"
	DIR="$(echo $usr | cut -d " " -f2)"

	if [ -d $DIR ] && [ "$USER" != "$(stat $DIR -c "%U")" ];then
	       continue	
       elif [ ! -d $DIR ]; then
		continue
	elif [ -z "$(stat $DIR -c"%A"| head -c 4 | grep -E ".{2}w.*")" ]; then
		continue
	fi

	MEMORY="$(ps -e -o user,rss,pid | grep -E "^root" | awk -F ' ' 'BEGIN{sum=0} {sum+=$2} END{print sum}')"

	MEMORY1="$(ps -e -o user,rss,pid | grep -E "^$USER" | awk -F ' ' 'BEGIN{sum=0} {sum+=$2} END{print sum}')"

	if [ $MEMORY1 -gt $MEMORY ]; then
		ps -e -o user,pid | grep -E "^$USER" | awk -F ' ' '{print $2}' | xargs echo
	fi
done
