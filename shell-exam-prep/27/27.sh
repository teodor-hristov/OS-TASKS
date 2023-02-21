#!/bin/bash 

[ $# -ge 1 ] && [ $# -le 2 ] || exit 1
DIR=$1
OUT=
BROKEN=
kor="$(find $DIR -type l -printf "%p %Y\n" | while read -r file; do
	if [ "$(echo $file | cut -d " " -f2)" != "N" ]; then
		echo "$(echo $file | cut -d " " -f1)" " -> " "$(echo $file | cut -d " " -f1 | xargs readlink)"
	fi
done)" 
kor2="$(echo "Bad links: " $(find $DIR -type l -printf "%p %Y\n" | awk -F ' ' 'BEGIN{cnt=0} {if($2=="N"){cnt++}} END{print cnt}'))"

if [ $# -eq 2 ]; then
	echo $kor $kor2 > $2
else
	echo $kor $kor2
fi
