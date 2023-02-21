#!/bin/bash

[ "$(whoami)" == "tedo3637" ] || [ "$(whoami)" == "oracle" ] || exit 1
[ -n "${ORACLE_HOME+}" ] || exit 1
usr="$(whoami)"
file="$(find "$(ORACLE_HOME)" -type f -name "adrci")"
[ -n "$file" ] || exit 1

command_out="$($file "exec=show homes")"

if [ "$command_out" != "No ADR homes are set" ]; then
	echo "$(echo "$command_out" | grep -v -E "ADR Homes:" | xargs stat -c "%s %n")"
fi

