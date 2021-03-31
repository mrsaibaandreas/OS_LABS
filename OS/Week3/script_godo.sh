#!/bin/bash

while read line
do
	IP=`echo $line| tr -s ' ' | cut -f 1 -d ' '`
	IP_FILTER=`echo $IP | egrep  '[1-9][0-9]{0,2}\.[1-9][0-9]{0,2}\.[1-9][0-9]{0,2}\.[1-9][0-9]'`
	echo $IP_FILTER
done < $1
