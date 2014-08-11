if [ $# -lt 1 ]
then
    echo "arena??"
    exit 0
fi
cp src/myalgo.h ../$1/src
cp src/template.cpp ../$1/src
cp sync.sh ../$1/
