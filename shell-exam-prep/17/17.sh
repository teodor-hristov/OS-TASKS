#!/bin/bash

[ "$(whoami)" = "root" ] || exit 1

cat /etc/passwd | awk -F ':' '{print $6"\n"}' | while read -r line; do
	PERMS="$(find $line -maxdepth 1 -wholename $line ! -perm -u+r 2>/dev/null)"
	if [ $PERMS ]; then
		echo $PERMS
	fi
	unset PERMS
done

cat /etc/passwd | awk -F ':' '$6 == "" {print $1"\n"}'
