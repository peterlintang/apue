#!/bin/bash

##find regular files in dir

DIR=$1
if test $# -ne 1; then
	echo "usage: $0 dir"
	echo "   find regular files in dir"
	exit 1
fi

for i in `find $DIR -type d`; do
	echo $i
done
