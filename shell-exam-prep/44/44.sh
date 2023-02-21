#!/bin/bash

[ $# -eq 2 ] || exit 1
in=$1
out=$2
[ -f "$in" ] || exit 1

inSize="$(cat $in | tr -d '\n' | wc -c)"
[ $inSize -le 524288 ] || exit 1

filedata="$(cat $in | xxd -p | tr -d '\n')"

data="$(while [ 1 ]; do
	filedata="$(echo "$filedata" | tail -c+4)"
	get="$(echo "$filedata" | head -c+4)"
	if [ -n "$get" ];then
		echo "\"0x$get\","
	else
		break
	fi

done | head -c-2)"

echo "const uint32_t arrN = $(echo "$inSize/2" | bc);"
echo "const uint16 data = {"$data"};"
