#!/bin/bash

[ $# -eq 2 ] || exit 1
DIR=$1
ARCH=$2

echo "$(find $DIR -maxdepth 1 -type f | grep -E "vmlinuz-([0-9]+[.]{1}){2}[0-9]+-$ARCH" | sort | tail -n1)"
