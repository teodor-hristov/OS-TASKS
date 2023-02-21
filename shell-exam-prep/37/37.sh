#!/bin/bash

[ $# -eq 1 ] || exit 1
FILE=$1
[ -f $FILE ] || exit 1

cat $FILE | awk -F ' ' '{print $2}' | sort | uniq -c | sort -n -r -k1,1 | awk -F ' ' '{print $2}' | while read -r website; do

http2="$(cat $FILE | grep -E "$website" | grep -E "HTTP/2.0" | wc -l)"
nonhttp2=$(($(cat $FILE | grep -E "$website" | wc -l)-$http2))
echo "$website HTTP/2.0 $http2 non-HTTP/2.0 $nonhttp2"

done

echo "$(cat $FILE | awk -F ' ' '{if($9>302){print $1}}' | sort | uniq -c | sort -n -r -k1,1 | head -n 5)"
