#!/bin/bash

[ $# -eq 2 ] || exit 1
TOSAVE=$1
DIR=$2
[ -d $DIR ] || exit 1

echo "hostname,phy,vlans,hosts,failover,VPN-3DES-AES,peers,VLAN Trunk Ports,license,SN,key" > $TOSAVE
find $DIR -type f | grep -E ".*.log$" | while read -r line; do
echo "$(echo "$(echo $line | basename $line | sed -e 's/.log//'),$(cat $line |  tail -n+2 | head -n7 | awk -F ':' '{print $2","}' | tail -c+2) $(cat $line | head -n 9 | tail -n 1 | sed -e 's/This platform has a //' -e 's/ license.//'),$(cat $line | tail -n 2 | awk -F ':' '{print $2","}' | tail -c+2)" | tr -d '\n' | head -c-1)"

done | sed -e 's/ //' >> $TOSAVE 
