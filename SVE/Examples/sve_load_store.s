    .text
    .align 4
    .type sve_load_store, %function
    .global sve_load_store
sve_load_store:
    ldr z0, [x0]
    str z0, [x1]

    ret
    .size sve_load_store, (. - sve_load_store)