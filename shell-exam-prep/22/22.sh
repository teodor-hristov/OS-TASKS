#!/bin/bash

[ $# -eq 1 ] || exit 1
[ "$(whoami)" = "root" ] || exit 1
USR=$1

echo "$(ps -e -o user | tail -n+2 | sort -k1,1 | uniq -c)" | while read -r usr; do
	if [ "$(echo $usr | cut -d " " -f2)" = "$USR" ]; then
		break
	fi
	echo "$(echo $usr | cut -d " " -f2)"
done

SECONDS=$(($(echo "$(ps -e -o etimes |tail -n+2 |  awk -F '\n' '{sum+=$1} END{print sum}')") / $(ps -e | wc -l)))
echo $SECONDS
H=$((($SECONDS / 360) % 60))
M=$((($SECONDS/ 60) % 60))
S=$(($SECONDS % 60))

echo $H":"$M":"$S

echo "$(ps -e -o user,uid,etimes | tail -n+2 | awk -F ' ' '$1 == "'$USR'"' | awk -F ' ' '$3 > "'$((2*$SECONDS))'"' | xargs kill )" 
