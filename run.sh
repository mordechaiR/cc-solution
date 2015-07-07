#!/bin/bash
# bash script to execute program
INPUTPATH=./tweet_input/shakes.txt
# compile sourcefile using g++ compiler, ignore C++ 11 warnings
g++ -std=c++11 src/main.cpp
# run program using INPUTPATH as command line argument
./a.out $INPUTPATH
