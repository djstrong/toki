#!/bin/bash
if [ "$1" == "" ]; then
	BYTES=10204
else
	BYTES=$1
fi
tr -dc "[:cntrl:]A-Za-z0-9.,!()[] \n{}\"';:" </dev/urandom | \
	tr "[:cntrl:]" " " | \
	head -c $BYTES | \
	sed "s/   /\n/g" | \
	sed "s/^ \+//" | \
	sed "s/ +$//" | \
	sed "/^$/d" | \
	sed "\${/^$/!s/$/\n/;}"
