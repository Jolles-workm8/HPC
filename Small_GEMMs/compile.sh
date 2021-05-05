#!/bin/bash

g++ -c gemm_ref.cpp
g++ -c driver.cpp
g++ -o driver gemm_ref.o driver.o
rm gemm_ref.o
rm driver.o
