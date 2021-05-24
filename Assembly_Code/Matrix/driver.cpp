#include <iostream>
#include <cstdint>
#include <cstdlib>

int main() {

uint32_t * l_a = new uint32_t[8];
uint32_t * l_b = new uint32_t[4];
uint32_t * l_c = new uint32_t[8];

for( unsigned short l_va = 0; l_va < 8; l_va++ ) {
        l_a[l_va] = (l_va+1);
        if(l_va<4){
            l_b[l_va] = (l_va+1);
        }
        l_c[l_va] = 0;
    }
gemm_asm_gp(l_a, l_b, l_c);


    return EXIT_SUCCESS;
}