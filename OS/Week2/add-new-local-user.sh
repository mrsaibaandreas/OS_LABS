#!/bin/bash
first_number=$1
second_number=$2
third_number=$3
if[ $first_number -gt $second_number ]
then
	if[ $first_number -gt $third_number ]
	then
		max=$first_number
		if[ $second_number -gt $third_number ]
		then
			min=$third_number
		else
			min=$second_number
		fi
	fi
fi
