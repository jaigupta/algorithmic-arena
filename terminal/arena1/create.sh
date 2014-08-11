#!/bin/bash
if [ $# -lt 1 ]
then
    echo "No Program name specified"
    exit 1
fi
if [ ! -e $1 ]
then
    mv *.cpp ../doneprogs/
    rm -f *.in *.out
    cp ../src/template.cpp $1.cpp
fi

