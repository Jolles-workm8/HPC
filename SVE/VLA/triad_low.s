  .text
  .align 4
  .type triad_low, %function
  .global triad_low
triad_low:

  mov x4, #0
  whilelt p0.s, x4, x0

  //jump to end if done
  b.none done

  //init z0 with 2.0
  fmov z0.s, #2.0

loop:
  ld1w z1.s, p0/z, [x1, x4, lsl #2]
  ld1w z2.s, p0/z, [x2, x4, lsl #2]

  fmla z1.s, p0/m, z0.s, z2.s

  st1w z1.s, p0, [x3, x4, lsl #2]

  incw x4
  
  whilelt p0.s, x4, x0
  b.any loop

done:

  ret
  .size triad_low, (. - triad_low)
