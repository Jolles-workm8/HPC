	.text
      .type gemm_asm_gp, %function
      .global gemm_asm_gp
      /*
       * Performs the matrix-multiplication C+=A*B
       * with the shapes (4x2) = (4x2) * (2x2).
       * The input-data is of type uint32_t.
       *
       * @param x0 pointer to A.
       * @param x1 pointer to B.
       * @param x2 pointer to C.
       */
gemm_asm_gp:
      // store
      stp x19, x20, [sp, #-16]!
      stp x21, x22, [sp, #-16]!
      stp x23, x24, [sp, #-16]!
      stp x25, x26, [sp, #-16]!
      stp x27, x28, [sp, #-16]!
      stp x29, x30, [sp, #-16]!

      //matrix-kernel!


      //load first row of c
      ldp w4, w5, [x2]
      ldp w6, w7, [x2, #8]

      //load first row of a
      ldp w8, w9, [x0]
      ldp w10, w11, [x0, #8]

      //load first value of b
      ldr w12,    [x1]

      //multiply and add
      madd w4, w8, w12, w4
      madd w5, w9, w12, w5
      madd w6, w10, w12, w6
      madd w7, w11, w12, w7



      //load second row of a
      ldp w8, w9, [x0, #16]
      ldp w10, w11, [x0, #24]

      //load second value of b
      ldr w12,    [x1, #4]

      //multiply and add
      madd w4, w8, w12, w4
      madd w5, w9, w12, w5
      madd w6, w10, w12, w6
      madd w7, w11, w12, w7


      //store first row of c
      stp w4, w5, [x2]
      stp w6, w7, [x2, #8]


      //load second row of c
      ldp w4, w5, [x2, #16]
      ldp w6, w7, [x2, #24]

      //load first row of a
      ldp w8, w9, [x0]
      ldp w10, w11, [x0, #8]

      //load third value of b
      ldr w12,    [x1, #8]

      //multiply and add
      madd w4, w8, w12, w4
      madd w5, w9, w12, w5
      madd w6, w10, w12, w6
      madd w7, w11, w12, w7



      //load second row of a
      ldp w8, w9, [x0, #16]
      ldp w10, w11, [x0, #24]

      //load fourth value of b
      ldr w12,    [x1, #12]

      //multiply and add
      madd w4, w8, w12, w4
      madd w5, w9, w12, w5
      madd w6, w10, w12, w6
      madd w7, w11, w12, w7


      //store second row of c
      stp w4, w5, [x2, #16]
      stp w6, w7, [x2, #24]





      // restore
      ldp x29, x30, [sp], #16
      ldp x27, x28, [sp], #16
      ldp x25, x26, [sp], #16
      ldp x23, x24, [sp], #16
      ldp x21, x22, [sp], #16
      ldp x19, x20, [sp], #16

      ret
      .size gemm_asm_gp, (. - gemm_asm_gp)
