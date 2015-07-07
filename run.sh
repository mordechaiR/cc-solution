#!/bin/bash
INPUTPATH=./tweet_input/shakes.txt
g++ -std=c++11 src/main.cpp 
./a.out $INPUTPATH
