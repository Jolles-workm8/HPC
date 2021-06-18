#!/bin/bash

gcc -c -g -march=armv8-a+sve triad_low.s
g++ -g -march=armv8-a+sve driver.cpp triad_low.o

armie -msve-vector-bits=128 ./a.out 5
