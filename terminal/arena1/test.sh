#!/bin/bash

BASE_PROJECT=$1

INPUTFILE="1"

if [ $# -gt 0 ]
then
    INPUTFILE=$BASE_PROJECT/in/$1
    OUTPUTFILE=$BASE_PROJECT/out/$1
fi

progname=run #`echo $1 | sed -e 's/^.*\\///'`
rm -f bin/algoout bin/$progname bin/diffout > /dev/null >> /dev/null

DEBUG_MODE=0

if [ $# -gt 1 ]
then
    if [ $2 -eq 1 ]
    then
	DEBUG_MODE=1
	echo "Running in Debug Mode"
	g++ -DJAI_ARENA -Wall -W -Wextra -g *.cpp -o bin/$progname
	bin/$progname < $INPUTFILE 
    fi   
fi

if [ $DEBUG_MODE -eq 0 ]
then
    g++ -Wall -W -Wextra -g *.cpp -o bin/$progname
fi

if [ ! -e bin/$progname ]
then
    echo "\nCompilation Error\n"
    exit 1
fi

if [ $DEBUG_MODE -eq 1 ]
then
    exit 1
fi


if [[ ! -e $INPUTFILE || ! -f $INPUTFILE ]]
then
    echo "[*] Could not find a valid input file. Redirecting to Terminal:"
    time bin/$progname
    exit 1
else
    echo -n Time taken:
    time bin/$progname < $INPUTFILE > bin/algoout
    echo -------------------------------
    echo
fi

if [[ -e $OUTPUTFILE && -f $OUTPUTFILE ]]
then
    diff $OUTPUTFILE bin/algoout > bin/diffout
    diffsize=`ls -l bin/diffout | cut -d' ' -f5`
    if [ $diffsize -eq 0 ]
    then
	echo Success!!
    else
	echo Failed!!
	echo "[*] ######  DIFF  ######"
	cat bin/diffout
	echo "    --------------------"
	echo
	echo "[*] ## EXPECTED OUTPUT ##"
	cat $OUTPUTFILE
	echo "    --------------------"
	echo 
	echo "[*] ## FOUND OUTPUT #####"
	cat bin/algoout
	echo "    --------------------"
    fi
else
    echo "[*] Could not find output file. Dumping to Terminal:"
    cat bin/algoout
fi