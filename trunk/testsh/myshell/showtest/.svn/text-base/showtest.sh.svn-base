#!/bin/bash

#test test -n
ready=1;
if test -n ${ready}; then
	echo string length is not zero
else
	echo string length is zero
fi

##test the dirr -q
if diff -q ./hello.txt ./hello2.txt >/dev/null 2>/dev/null; then
	echo  equal
fi


#test read from file
token=""
while read token ; do
	echo $token
done << EOF
$(cat ./hello.txt)
EOF
