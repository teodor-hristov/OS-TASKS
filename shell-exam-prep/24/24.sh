#!/bin/bash
[ $# -le 2 ] || exit 1
DIR=$1
if [ $# -eq 2 ]; then
	find $DIR -type f -printf "%p %n\n" 2>/dev/null | awk -F ' ' '{if($2 >= "'$2'"){print $1}}' | sort | uniq
else
	find $DIR -type l -printf "%p %n %Y\n" 2>/dev/null | awk -F ' ' '{if($3=="N"){print}}'
fi

