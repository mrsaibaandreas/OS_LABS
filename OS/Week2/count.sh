#!/bin/bash
director=$1 #the directory
output=$2   #the output file
chars=0     #the characters
files=`find $director/*.txt`
for i in $files
do
actual_chars=`wc -c $i | cut -f 1 -d ' '`
chars=`expr $chars + $actual_chars`
echo --$i ---$actual_chars >>$output
done
echo TOTAL $chars >>$output
