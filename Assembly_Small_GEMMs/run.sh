#!/bin/bash

gcc -c -g gemm_asm_asimd_19_4_4.s
gcc -c -g gemm_asm_asimd_32_32_32.s
g++ -g -O3 driver.cpp gemm_asm_asimd_16_4_4.o gemm_asm_asimd_16_4_12.o
