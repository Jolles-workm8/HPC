    .text
    .align 4
    .type sve_mul_load_store, %function
    .global sve_mul_load_store
sve_mul_load_store:
    ptrue p0.s, MUL3
    ld1w {z0.s}, p0/z, [x0]
    str z0, [x1]

    ret
    .size sve_mul_load_store, (. - sve_mul_load_store)