#!/bin/bash

gcc -c Hello_World.s
od -A x4 -t x1 Hello_World.o > Hello_World.hex

gcc Hello_World.s 
./a.out

objdump --syms -S -d Hello_World.o > Hello_World.dis