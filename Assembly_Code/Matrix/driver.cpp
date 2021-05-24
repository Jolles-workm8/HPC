#include <iostream>
#include <cstdint>
#include <cstdlib>

extern "C" {

  void gemm_asm_gp( uint32_t const * i_a,
                 uint32_t const    * i_b,
                 uint32_t          * o_c);
}
int main() {
  uint32_t l_a[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  uint32_t l_b[4] = { 9, 10, 11, 12 };
  uint32_t l_c[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };



  gemm_asm_gp( l_a, l_b, l_c );

  for(int i = 0; i<4; i++){

    std::cout << l_c[i] << " "<< l_c[i+4] << std::endl;

  }

  //test for correctness
  if(l_c[0] == 59 && l_c[1] == 78 && l_c[2] == 97 && l_c[3] == 116 && l_c[4] == 71 && l_c[5] == 94 && l_c[6] == 117 && l_c[7] == 140){
  std::cout << "test successfull" << std::endl;
  }
  else{
  std::cout << "test error" << std::endl;
  }

  return EXIT_SUCCESS;
}
