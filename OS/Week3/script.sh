#!/bin/bash

input_file=$1
while read line
do
ip=`echo $line | egrep '^[1-9]{1,3}' | cut -f 1 -d ' '`
echo $ip
#for i in 4
#do
#	var=`cut -f $i -d '.'`
#    echo echo $var
#	if [ $var -gt 0 & $var -lt 256 ]
#	then 
#		ip=-1
#		break
#	fi	  
#done
#if [ ip -eq -1 ]
#then
#	continue
#fi
#ech#o $ip     
done < $input_file 

#cat $input_file
