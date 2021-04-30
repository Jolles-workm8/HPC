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
1. [alt text](https://github.com/Jolles-workm8/HPC/blob/main/Pipelining/fmla_fmul.png)
