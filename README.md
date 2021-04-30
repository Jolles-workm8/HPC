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

3. The result of the benchmarking using one source register were:
  ![alt text](https://github.com/Jolles-workm8/HPC/blob/main/Pipelining/fmul_fmla_src.png)
  
4. The result of the benchmarking using one destination register were:
  ![alt text](https://github.com/Jolles-workm8/HPC/blob/main/Pipelining/fmul_fmla_dst.png)
