#!/bin/sh 

if [ $# -eq 0 ] 
then
    echo "Please enter which to test"
    exit 0
fi

echo "ARG1: [$1]"

TEST=$1

if [ $TEST = "core" ] 
then
    ./build/Library/CoreLib/test/core_test $2 $3 $4
    exit 0  
fi

if [ $TEST = "gui" ] 
then
    ./build/test_gui
    exit 0  
fi


if [ $TEST = "net" ] 
then
    echo "Run Network Engine Test"
    ./build/Library/NetEngine/test/net_engine_test $2 $3 $4
    exit 0  
fi


echo "Unknown Test"
## Run DemoApp1
# ./build/test_main $2 $3 $4 

