#!/bin/bash

gcc -c -g gemm_asm_asimd_16_4_4.s
g++ -g driver.cpp gemm_asm_asimd_16_4_4.o