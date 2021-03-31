#!/bin/bash
list=`ls -l | tr -s ' ' | cut -f 5 -d ' '`
result=0
for i in $list
do
	#echo "my_value $i"
        #result = result +i
	result=`expr $result + $i`
done
echo "result is $result"

if test 100000000 -gt $result
then
	echo "result is to small"
fi

