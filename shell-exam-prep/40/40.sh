# !/bin/bash

[ $# -eq 3 ] || exit 1
pswd=$1
cfg=$2
cnf=$3

find "$cnf" -type f | grep -E ".cfg$" | while read -r file; do
	error="$(cat "$file" | grep -n -E -v "((^[#].*)|([ ]*[{].*[}][;][ ]*$))")"	
	if [ -n "$error" ];then
		echo "$error"
	else
		username="$(echo $cfg | grep -E -o -v "[.]cfg")"
		if [ -z "$(cat $pswd | grep "$username")" ];then
			pass="asdasdasdasdasds"
			echo "$username:$pass" >> $pswd

		fi	
	fi
done

	

