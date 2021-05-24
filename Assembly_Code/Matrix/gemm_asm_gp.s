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

        //calculating c11
        ldr w0, [x0]
        ldr w1, [x0, #4]

        ldr w2, [x1]
        ldr w3, [x1, #8]

        ldr w4, [x2]

        madd w4, w0, w3, w4
        madd w4, w1, w3, w4

        str w4, [x2]

        //calculating c12
        ldr w0, [x0]
        ldr w1, [x0, #4]

        ldr w2, [x1, #4]
        ldr w3, [x1, #12]

        ldr w4, [x2, #4]

        madd w4, w0, w3, w4
        madd w4, w1, w3, w4

        str w4, [x2, #4]


        //calculating c21
        ldr w0, [x0, #8]
        ldr w1, [x0, #12]

        ldr w2, [x1]
        ldr w3, [x1, #8]

        ldr w4, [x2, #8]

        madd w4, w0, w3, w4
        madd w4, w1, w3, w4

        str w4, [x2, #8]


        //calculating c22
        ldr w0, [x0, #8]
        ldr w1, [x0, #12]

        ldr w2, [x1, #4]
        ldr w3, [x1, #12]

        ldr w4, [x2, #12]

        madd w4, w0, w3, w4
        madd w4, w1, w3, w4

        str w4, [x2, #12]


        //calculating c31
        ldr w0, [x0, #16]
        ldr w1, [x0, #20]

        ldr w2, [x1]
        ldr w3, [x1, #8]

        ldr w4, [x2, #16]

        madd w4, w0, w3, w4
        madd w4, w1, w3, w4

        ldr w4, [x2, #16]

        //calculating c32
        ldr w0, [x0, #16]
        ldr w1, [x0, #20]

        ldr w2, [x1, #4]
        ldr w3, [x1, #12]

        ldr w4, [x2, #20]

        madd w4, w0, w3, w4
        madd w4, w1, w3, w4

        ldr w4, [x2, #20]

        
        // restore
        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_gp, (. - gemm_asm_gp)