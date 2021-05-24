#!/bin/bash

gcc -c -g gemm_asm_gp.s 
g++ -g driver.cpp gemm_asm_gp.o
