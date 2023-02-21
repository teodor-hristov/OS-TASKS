#!/bin/bash

ps -e -o uid | tail -n+2 | sort | uniq | while read -r uid; do
MID=$(ps -e -o uid,rss,pid | awk -F ' ' 'BEGIN{cnt=0;sum=0;} {if($1=="'$uid'"){sum+=$2; cnt++}} END{print "'$uid'"" "int(sum/cnt)}')
	ps -e -o uid,rss,pid | tail -n+2 |  while read -r proc; do

		if [ "$(echo $proc | cut -d ' ' -f2)" -ge "$(echo $MID | cut -d ' ' -f2)" ] && [ "$(echo $proc | cut -d ' ' -f1)" == "$(echo $MID | cut -d ' ' -f1)" ]; then
			echo "kill " $proc
		fi

	done
done
