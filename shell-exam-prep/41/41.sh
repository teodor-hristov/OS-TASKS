#!/bin/bash

[ $# -eq 3 ] || exit 1
file=$1
key=$2
value=$3

alabala="$(cat $file | while read -r line; do
	maybe_comment="$(echo $line | grep -E "^[ ]*[#].*")"
	if [ -z "$maybe_comment" ];then
		wanted_key="$(echo $line | grep -E "^[ ]*$key[ ]*=.*")"	
		if [ -n "$wanted_key" ];then
			alabala="kavarma"
			echo "#$line #edited on "$(date)" by "$(whoami)""
			echo "$key = $value #added on "$(date)" by "$(whoami)""
		else
			echo "$line"
		fi
	else
		echo "$line"
	fi
done)"

echo "$alabala"
if [ -z "$(echo "$alabala" | grep -E "^[ ]*$key[ ]*=.*")" ];then
echo "$key = $value #added on "$(date)" by "$(whoami)""	
fi
