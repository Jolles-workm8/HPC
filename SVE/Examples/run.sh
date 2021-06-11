#!/bin/bash

gcc -c -g -march=armv8-a+sve sve_load_store.s 
gcc -c -g -march=armv8-a+sve sve_predicated_load_store.s 
gcc -c -g -march=armv8-a+sve sve_predicated_argument_load_store.s
gcc -c -g -march=armv8-a+sve sve_mul_load_store.s
g++ -g -march=armv8-a+sve driver.cpp sve_load_store.o sve_predicated_load_store.o sve_predicated_argument_load_store.o sve_mul_load_store.o

echo "Kernel 0"
echo "instruction count:"
echo "128 Bit vector"
armie -msve-vector-bits=128 -i libinscount_emulated.so ./a.out 0
echo "256 Bit vector"
armie -msve-vector-bits=256 -i libinscount_emulated.so ./a.out 0
echo "512 Bit vector"
armie -msve-vector-bits=512 -i libinscount_emulated.so ./a.out 0

echo "Kernel 1"
echo "instruction count:"
echo "128 Bit vector"
armie -msve-vector-bits=128 -i libinscount_emulated.so ./a.out 1
echo "256 Bit vector"
armie -msve-vector-bits=256 -i libinscount_emulated.so ./a.out 1
echo "512 Bit vector"
armie -msve-vector-bits=512 -i libinscount_emulated.so ./a.out 1

echo "Kernel 2"
echo "instruction count:"
echo "128 Bit vector"
armie -msve-vector-bits=128 -i libinscount_emulated.so ./a.out 2
echo "256 Bit vector"
armie -msve-vector-bits=256 -i libinscount_emulated.so ./a.out 2
echo "512 Bit vector"
armie -msve-vector-bits=512 -i libinscount_emulated.so ./a.out 2

echo "Kernel 3"
echo "instruction count:"
echo "128 Bit vector"
armie -msve-vector-bits=128 -i libinscount_emulated.so ./a.out 3
echo "256 Bit vector"
armie -msve-vector-bits=256 -i libinscount_emulated.so ./a.out 3
echo "512 Bit vector"
armie -msve-vector-bits=512 -i libinscount_emulated.so ./a.out 3

echo "Kernel 0"
echo "instruction count:"
echo "128 Bit vector"
armie -e libmemtrace_sve_128.so -i libmemtrace_emulated.so -- ./a.out 0
echo "256 Bit vector"
armie -e libmemtrace_sve_256.so -i libmemtrace_emulated.so ./a.out 0
echo "512 Bit vector"
armie -e libmemtrace_sve_512.so -i libmemtrace_emulated.so ./a.out 0

echo "Kernel 1"
echo "instruction count:"
echo "128 Bit vector"
armie -e libmemtrace_sve_128.so -i libmemtrace_emulated.so ./a.out 1
echo "256 Bit vector"
armie -e libmemtrace_sve_256.so -i libmemtrace_emulated.so ./a.out 1
echo "512 Bit vector"
armie -e libmemtrace_sve_512.so -i libmemtrace_emulated.so ./a.out 1

echo "Kernel 2"
echo "instruction count:"
echo "128 Bit vector"
armie -e libmemtrace_sve_128.so -i libmemtrace_emulated.so ./a.out 2
echo "256 Bit vector"
armie -e libmemtrace_sve_256.so -i libmemtrace_emulated.so ./a.out 2
echo "512 Bit vector"
armie -e libmemtrace_sve_512.so -i libmemtrace_emulated.so ./a.out 2

echo "Kernel 3"
echo "instruction count:"
echo "128 Bit vector"
armie -e libmemtrace_sve_128.so -i libmemtrace_emulated.so ./a.out 3
echo "256 Bit vector"
armie -e libmemtrace_sve_256.so -i libmemtrace_emulated.so ./a.out 3
echo "512 Bit vector"
armie -e libmemtrace_sve_512.so -i libmemtrace_emulated.so ./a.out 3

