#!/bin/bash

[ $# -eq 1 ] || exit 1
DIR=$1
SAVE="pimp.tmp"
echo "" >> $SAVE

find $DIR -type f | grep -E "^[^_]*_report-[0-9]+.tar$" | while read -r file; do
	
if [ -z "$(cat $SAVE | grep -F "$(sha256sum $file)")" ];then 
		echo "$(sha256sum $file)"
		meow="$(tar --list -f $file | grep -E -o "meow.txt")"
		if [ -n "$meow" ];then
			mkdir -p "./extracted/"
			tar --extract -f $file "$meow"
			mv "$meow" "./extracted/$(echo $file | cut -d "_" -f1)_$(echo $file | grep -E -o "[0-9]+.tar$" | cut -d "." -f1)"
		fi
	fi

done >> $SAVE
