#!/bin/bash

echo "$(cat /etc/passwd | awk -F ':' '{print $6}')" | while read folder; do
	find $folder -type f -printf "%u %p %C@\n" 2>/dev/null | sort -n -k3,3 | tail -n1 
done | sort -n -k3,3 | tail -n1 | cut -d " " -f1
