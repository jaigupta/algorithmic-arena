#!/bin/bash
if [ $# -lt 3 ]
then
	echo "Provide Contest name, Arena Prefix and arena count"
	exit 1
fi

for (( i = 1; i <= $3; i++ ))
do
	`cp doneprogs/$1_$i.cpp $2$i/prog.cpp`
done