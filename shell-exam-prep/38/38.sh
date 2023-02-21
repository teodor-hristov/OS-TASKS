#!/bin/bash

[ $# -eq 2 ] || exit 1
REPO=$1
PACKAGE=$2
[ -d $REPO ] && [ -d $PACKAGE ] || exit 1

tar -cz -f "my_package.tar.xz" $PACKAGE
SHA="$(sha256sum "my_package.tar.xz" | cut -d " " -f1)"
rm "my_package.tar.xz"

VER="$(cat "$PACKAGE/version")"
PACK_INFO="$(echo "$PACKAGE-$VER $SHA")"

pack_inside="$(cat "$REPO/db" | grep -E "$PACKAGE")"
if [ -z "$pack_inside" ];then
	echo $PACK_INFO >> "$REPO/db"
	tar -cz -f "$REPO/packages/$SHA.tar.xz" $PACKAGE
else
	old_ver="$(echo $pack_inside | cut -d " " -f1 | sed -e  "s/$PACKAGE-//")"
	if [ "$old_ver" == "$(echo "$old_ver $VER" | tr ' ' '\n' | sort | head -n1)" ];then
		#mahame ot db
		old_sha_pack="$(cat "$REPO/db" | grep "$PACKAGE" | cut -d " " -f2)" 
		echo "$(cat "$REPO/db" | grep -v "$PACKAGE")" > "$REPO/db"
		find "$REPO/packages" -type f | grep "$old_sha_pack" | xargs rm
		#dobavqme noviq	
        	echo $PACK_INFO >> "$REPO/db"
          	tar -cz -f "$REPO/packages/$SHA.tar.xz" $PACKAGE
	fi
fi
