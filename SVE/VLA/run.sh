#!/bin/bash

gcc -c -g -march=armv8-a+sve triad_low.s
g++ -g -march=armv8-a+sve driver.cpp triad_low.o

armie -msve-vector-bits=128 ./a.out 4
armie -msve-vector-bits=128 ./a.out 9
armie -msve-vector-bits=128 ./a.out 17
armie -msve-vector-bits=128 ./a.out 123
armie -msve-vector-bits=512 ./a.out 4
armie -msve-vector-bits=512 ./a.out 9
armie -msve-vector-bits=512 ./a.out 17
armie -msve-vector-bits=512 ./a.out 123


