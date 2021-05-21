#!/bin/bash

gcc -c -g load.s 
g++ -g driver.cpp load.o