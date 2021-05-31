#include <iostream>


extern "C" {
    void gemm_asm_asimd_16_4_4(uint32_t const * i_a,
                 uint32_t const    * i_b,
                 uint32_t          * o_c);
}

int main(){
    uint32_t * l_a = new uint32_t[64];
    uint32_t * l_b = new uint32_t[16];
    uint32_t * l_c = new uint32_t[64];

    for(size_t i=0; i<64; i++){
        l_a[i]=i+1;
        l_c[i]=0;
    }

    for(size_t i=0; i<16; i++){
        l_b[i]=i+1;
    }

    gemm_asm_asimd_16_4_4(l_a, l_b, l_c);

    for(size_t i=0; i<64; i++){
        if(i%4 ==0 ){
            std::cout << "\n";
        }
        std::cout<< " | " << l_c[i] << " | ";       
        
    }

}