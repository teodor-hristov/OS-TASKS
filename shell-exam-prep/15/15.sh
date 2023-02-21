#!/bin/bash

[ $# -eq 1 ] || exit 1

DIR=$1

[[ -d $DIR  ]] || exit 1
(find $DIR -xtype l 2>/dev/null) | while read file; do
	echo $file
done 

