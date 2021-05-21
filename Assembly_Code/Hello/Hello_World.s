        .section .rodata
my_msg: .asciz "Hello World \n"

        .text 
        .global main

        // print hello world  and return 0

main: stp   x29, x30, [sp, #-16]
        // print hello world by calling printf
      adr   x0, my_msg
      bl    printf
      
      //return 0

      mov   w0, #0
      ldp   x29, x30, [sp], #16
      ret

      // size of main section
      .size main, (. - main)
