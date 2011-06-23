#!/bin/bash
#sets up network for use on swarms beagle platform
#called in ../pyDriveLink.py

idealNetIp='192.168.1.100'

localIPNet=$( ifconfig eth0 | egrep "192.168.1.10" | cut -f2 -d':' | cut -f1 -d ' ' )
echo "current ip:" $localIPNet

if [ $localIPNet ]; then
	echo "network on 192.168.1.10*"
	if [ $localIPNet = $idealNetIp ];then
		echo "network address setup properly on ip:", $idealNetIp
	else
		echo "taking network down:"
		echo "see you at", $idealNetIp 
		sleep 1
		ifconfig eth0 down
		ifconfig eth0 $idealNetIp netmask 255.255.255.0 up

	fi
fi

