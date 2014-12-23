#!/bin/bash


#
# 0 success
# 1 failed
#
print_hello() {
	echo "hello"
	return 0;
}

print_goodbye() {
	echo "good bye"
	return 1;
}

print_no () {
	echo "say here"
}

if print_hello && print_goodbye && print_no; then
	echo "done";
else
	echo "failed";
fi 
