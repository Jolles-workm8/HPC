

      .text
      .align 4
      .type   copy_asm, %function
      .global copy_asm
copy_asm:

      
      ldp w2, w3, [x0]
      stp x2, x3, [x1]
      ldp w2, w3, [x0, #8]
      stp x2, x3, [x1, #16]
      ldp w2, w3, [x0, #16]
      stp x2, x3, [x1, #32]
      ldr w2,     [x0, #24]
      str x2,     [x1, #48]



      ret
      .size copy_asm, (. - copy_asm)
