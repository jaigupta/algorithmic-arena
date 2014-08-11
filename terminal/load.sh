if [ $# -lt 2 ]
then
    echo "Enter path bollowed by new prog name"
    exit 1
fi
mv *.cpp ../doneprogs/
mv $1 $2.cpp
