    .text
    .align 4
    .type sve_predicated_load_store, %function
    .global sve_predicated_load_store
sve_predicated_load_store:
    ptrue p0.s
    ld1w {z0.s}, p0/z, [x0]
    str z0, [x1]

    ret
    .size sve_predicated_load_store, (. - sve_predicated_load_store)