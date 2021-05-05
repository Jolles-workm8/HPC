#include "gemm_ref.h"

void gemm_ref( float const * i_a,
               float const * i_b,
               float       * io_c,
               unsigned int  i_m,
               unsigned int  i_n,
               unsigned int  i_k,
               unsigned int  i_lda,
               unsigned int  i_ldb,
               unsigned int  i_ldc ){


  float value = 0;
  for(int l_m = 0; l_m < i_m; l_m ++){
    for(int l_n = 0; l_n < i_n; l_n ++){
      for(int l_k = 0; l_k < i_k; l_k ++){
        value += (i_a[l_m + l_k * i_lda] * i_b[l_k + l_n * i_ldb]);
      }
      io_c[l_m + l_n * i_ldc] += value;
      value = 0;
    }
  }
}
