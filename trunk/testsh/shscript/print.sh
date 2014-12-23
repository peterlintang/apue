#!/bin/bash
useage() {
	printf "$1"
}
if [ $# != 1 ]; then
	useage "print.sh string\n"
	exit 1
fi
printf "Hello %s\n" $1
