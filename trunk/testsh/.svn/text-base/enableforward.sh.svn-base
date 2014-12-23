#!/bin/bash
enable_ip_forward=`cat /proc/sys/net/ipv4/ip_forward`
if test $enable_ip_forward = 1 ; then
	echo "already enable ip forward"
else
	echo "1">/proc/sys/net/ipv4/ip_forward
fi
#ifconfig eth0 169.254.255.104 netmask 255.255.255.0


