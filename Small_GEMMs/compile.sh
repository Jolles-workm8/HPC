#!/bin/bash

g++ -c -O3 -I/home/max/software/libxsmm/include driver.cpp -pthread -lxsmm -L${HOME}/software/libxsmm/lib /lib64/libopenblas.so.0 -lm -ldl
g++ -c gemm_compiler_32_32_32_32_32_32.cpp
g++ -c gemm_ref.cpp
g++ -o main gemm_ref.o gemm_compiler_32_32_32_32_32_32.o driver.o

