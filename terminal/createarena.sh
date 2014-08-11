#!/bin/bash

if [ $# -lt 1 ]
then
    echo "Arena name?"
    exit 1
fi

if [ ! -e doneprogs ]
then
    mkdir doneprogs
fi

if [ -e $1 ]
then
    echo "Arena already exists"
    echo "Removing the previous arena"
    rm -rf $1
fi

mkdir $1
mkdir $1/bin
cp test.sh $1
cp start.sh $1
cp clean.sh $1
cp comparer.sh $1
cp create.sh $1
