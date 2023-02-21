#!/bin/bash

for file in $@; do
	is_multiline="$(cat $file | head -n 1 | grep -E "[(]")"
	serial=
	if [ -z "$is_multiline" ];then
		serial="$(cat "$file" | head -n 1 | awk -F ' ' '{print $7}')"	
	else
		serial="$(cat "$file" | head -n 2 | grep -E ";" | awk -F ';' '{print $1}')"
	fi
	
	value="$(echo "$(date '+%Y%m%d')-$(echo "$serial" | head -c-3)" | bc)"
	if [ "$value" != "0" ]; then
		echo "$(echo "$value+1" | bc)"
	else
		echo "$(date '+%Y%m%d')00"
	fi

	cat $file | sed -e 's/'$serial'/'$value'/' > $file
done
