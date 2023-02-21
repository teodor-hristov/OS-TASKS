#!/bin/bash
[ $# -eq 2 ] || exit 1
src=$1
dst=$2

[ -d "$src" ] || exit 1

dst=$(echo "$dst"| head -c-2)

find $src -type f | grep -E "[.]{1}jpg$" | while read -r file; do
	clean_name="$(echo $file | tr -s ' ' | sed -e 's/\/ /\//')"
	only_jpg="$(echo $clean_name | sed -e 's/.jpg//' )"
	brackets="$(echo "$only_jpg" | grep -E -o "[(][^(]*[)]")"
	last_bracket="$(echo $brackets | grep -E -o "[(][^(]*[)]$")"
	heading="$(echo "$only_jpg" | sed -e 's/([^(]*)//g' | tr -s ' ')"
	#hacky
	if [ -z "$last_bracket" ];then
		last_bracket="misc"
	fi

	album="$(echo "$last_bracket" | sed -e 's/(//g' -e 's/)//g')"
	date="$(stat "$file" -c "%y")"
	sha256_16="$(sha256sum "$file" | head -c16)"
	
	orginalda="$dst/images/$sha256_16.jpg"
	mkdir -p "$orginalda" 

	d1="$dst/by-date/$date/by-album/$album/by-title"
	d2="$dst/by-date/$date/by-ebi-si-maikata-portokal/$album"
	
	mkdir -p $d1 $d2
	
	heading="$(echo "$heading" | tail -c +3)"

	ln -s "$d1/$heading.jpg" "$orginalda"	
	#ln -s "$orginalda" "$d2/$heading.jpg" 	
done
