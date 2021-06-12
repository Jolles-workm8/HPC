# High-Performance-Computing
This git contents the tasks of the course "HPC"-Computing at the FSU-Jena.
The lecture is hold by Alexander Breuer.


[Lecture-Homepage](https://scalable.uni-jena.de/opt/hpc/index.html)


## Contents

[TOC]

## Mircobenchmarks
Mircobenchmarking of the Neoverse N2 ARM-Processor in the aws Grvaiton V2 Server.


## Bits
1. Printing bits of variable datatypes.

2. Bitmanipulation of various inputs.

3. The variable `unsigned int i_vec_instr` encodes a Floating-point fused Multiply-Add to accumulator vector-operation and contains an instruction-vector which contains the source registers, the destination register, the (byte)-length of the participating data.
This instruction multiplies 2 floating-point values and adds the product to the corresponding vector element. The bits 0-4 (Rd) and 5-9 (Rn) are encoding the registers where the sourcedata can be found. The bits 16-20 (Rm) are encoding the destination register.

## Pipelining
1. The metrics in the [Arm Neoverse N1 Software Optimization Guide](https://developer.arm.com/documentation/swog309707/a) were:
![alt text](https://github.com/Jolles-workm8/HPC/blob/main/Pipelining/fmla_fmul.png)
2. We can calculate the theoretical GFLOP/s via : Clockcycles * ASIMD (128Bit per Operation) * Throughput * FMA / Latency(just one operation at a time)

Operation | Calculation | Result
--- | --- | ---
fmul       | 2.5*10^9 * 4 * 2 * 2 / 4 | 10 GFlop/s      
fmla       | 2.5*10^9 * 4 * 2 / 3     | 6.66666 GFlop/s

3. & 4. The result of the benchmarking using one source register were:
  ![alt text](https://github.com/Jolles-workm8/HPC/blob/main/Pipelining/fmul_fmla_src.png)

5. The result of the benchmarking using one destination register were:
  ![alt text](https://github.com/Jolles-workm8/HPC/blob/main/Pipelining/fmul_fmla_dst.png)

You can find the .csv files and the code in /Pipelines

## Small GEMM's
1. You can find the code in the folder Small_GEMMs
2. The number of required operations to solve the Matrix-Matrix product of A * B, given A is a M * K Matrix and B is a K * N Matrix is :
   2 * K * M * N

Performance of the gemm kernels with different optimization levels in GFLOP's:

type | gemm_ref without optimization | gemm_ref with O2 | gemm_ref with O3 | libxsmm Kernel
--- | --- | --- | --- | ---
lambda: 4 | 0.308438 | 1.52468 | 1.35914 | 1.80327
lambda: 8 | 0.331801 | 1.99553 | 1.87899 | 3.63342
lambda: 12 | 0.337057 | 2.17769 | 2.08614 | 4.45306
lambda: 16 | 0.341165 | 2.20369 | 2.14876 | 4.69007
lambda: 24 | 0.333424 | 2.31289 | 2.26535 | 4.76983
lambda: 32 | 0.330431 | 2.36279 | 2.32706 | 5.02721
lambda: 48 | 0.327675 | 2.41029 | 2.38561 | 5.2072
lambda: 64 | 0.324477 | 2.42677 | 2.4125 | 5.31401
gemm_compiler_mnk: | 0.371008 | 2.66795 | 2.33032 | -
gemm_compiler_nkm: | 0.36406 | 2.41972	| 11.9447 | - 


## Assembly on AArch64

1. Find our approach in to the first exercise in ./Assembly_code/Hello

2. 
..1. The contents on the registers are:
..* X1:400
..* X2:400
..* X3:500
..* X4:600
..* X5:700

..2. 
..* not ok #1 :
    ==1174859== Invalid read of size 8
    ==1174859== at 0x40074C: main (driver.cpp:18)
    ==1174859== Address 0x4d03ce8 is 24 bytes after a block of size 80 in arena "client"

    The call a+12 is out of bounds because we allocated l_a just for 10 64-bit unsigned integers.

    ==1174859== Invalid read of size 8
    ==1174859== at 0x400774: load_asm (load.s:7)
    ==1174859== Address 0x4d03ce8 is 24 bytes after a block of size 80 in arena "client"

    The problem is the same: we can't load from the adress since it has no data. Notice that the error valgrind gives us is the same in driver.cpp and load.s.

    ==1175464== Invalid read of size 8
    ==1175464== at 0x400778: load_asm (load.s:8)
    ==1175464== Address 0x4d03cf8 is 24 bytes before an unallocated block of size 4,121,296 in arena "client"

    The Adress following the one above, since we load a pair of values, has no allocated value to it at all and is "hanging freely" in our main memory. This explains the 'before an unallocated block of size 4,121,296' bytes.


..* not ok #2:

    ==1175970== Invalid read of size 8
    ==1175970== at 0x400774: load_asm (load.s:7)
    ==1175970== Address 0x4d03cd0 is 0 bytes after a block of size 80 alloc'd
    ==1175970== at 0x4867DD8: operator new[](unsigned long) (vg_replace_malloc.c:431)
    ==1175970== by 0x4006F7: main (driver.cpp:9)    

    X0 is the 9th allocated memory register of our array. Increasing it by one with the advance operator ! X0 has the value of l_a[10]. In the following loadpair command the first valu can be loaded (as the last value of l_a) and the folloing value for X3 is missing. This explains the error message "0 bytes after allocated block' sine we are looking at the next 64 bit after the array l_a.


    ==1175970== Invalid read of size 8
    ==1175970== at 0x400778: load_asm (load.s:8)
    ==1175970== Address 0x4d03cd8 is 8 bytes after a block of size 80 alloc'd
    ==1175970== at 0x4867DD8: operator new[](unsigned long) (vg_replace_malloc.c:431)
    ==1175970== by 0x4006F7: main (driver.cpp:9)

    Now we do a load pair but we advance X0 by 16. Knowing that X0 is representing the 9th entry of l_a this means we look at the virtual 11th entry of l_a with doesn't exist. This explains the error message that we are 8 byte (=64bit) behind the last allocated block. This makes sense since l_a has only 10 netries.




..* not ok #3:

    ==1176053== Invalid read of size 8
    ==1176053== at 0x400778: load_asm (load.s:8)
    ==1176053== Address 0x4d03cd0 is 0 bytes after a block of size 80 alloc'd
    ==1176053== at 0x4867DD8: operator new[](unsigned long) (vg_replace_malloc.c:431)
    ==1176053== by 0x4006F7: main (driver.cpp:9)

    Very similiar to the one before. Now X0 starts as the 7th entry of l_a. Increasing it by 8 byte in l:6 makes it 8th entry. Loading from this adrees advancing by 16 Byte makes it the 11th entry of l_a which doesnt exist. This explains the error message 0 byte behinf allocated block.
   

3.

4.

## Assembly Blocks

1. You can find our Code in ./Assembly_BuildingBlocks . Our Teamname is: Gipfelstürmer.

Team | Time(s) | #executions | GFLOPs | %peak | Kernel
--- | --- | --- | --- | --- | ---
Gipfelstürmer | 2.52 | 100000000 | 20.30 | 50.8 | 16_4_4
Gipfelstürmer | 5.04 | 100000000 | 30.46 | 76.14 | 16_4_12

## Assembly Small Gemm's

Team | Time(s) | #executions | GFLOPs | %peak | Kernel
--- | --- | --- | --- | --- | ---
Gipfelstürmer | 3.78 | 100000000 | 16.04 | 40.1 | 19_4_4
Gipfelstürmer | 1.74 | 1000000 | 37.54 | 93.8 | 32_32_32

## SVE

Find the code for this exercise in ./SVE
Running the bash script "run.sh" will compile and execute the code.
1. The scrip executes four examples each with vector lenghts of 128. You can run the code yourself by using "a.out" after running the bash script.
2. The number of emulated instruction are printed when using the script.

Example | Instructions
--- | --- 
sve_load_store | 2
sve_predicated_load_store | 3
sve_predicated_argument_load_store | 3
sve_mul_load_store | 3


3. libmemtrace_emulated.so still throws an error and won't output the correct data.
