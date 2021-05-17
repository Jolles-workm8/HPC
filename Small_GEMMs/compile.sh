#!/bin/bash

g++ -c -O3 -I/home/julius/software/libxsmm/include driver.cpp 
g++ -c -O3 gemm_compiler_32_32_32_32_32_32.cpp
g++ -c -O3 gemm_ref.cpp
g++ -o main gemm_ref.o gemm_compiler_32_32_32_32_32_32.o driver.o -pthread -lxsmm -L${HOME}/software/libxsmm/lib /lib64/libopenblas.so.0 -lm -ldl

