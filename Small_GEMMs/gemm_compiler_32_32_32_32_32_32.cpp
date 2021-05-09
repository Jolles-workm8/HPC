#include "gemm_compiler_32_32_32_32_32_32.hpp"

void gemm_compiler_32_32_32_32_32_32_mnk(float const *i_a, float const *i_b,
                                         float *io_c) {
  for (int l_m = 0; l_m < 32; l_m++) {
    for (int l_n = 0; l_n < 32; l_n++) {
      for (int l_k = 0; l_k < 32; l_k++) {
        io_c[l_m + l_n * 32] += (i_a[l_m + l_k * 32] * i_b[l_k + l_n * 32]);
      }
    }
  }
}

void gemm_compiler_32_32_32_32_32_32_nkm(float const *i_a, float const *i_b,
                                         float *io_c) {
  for (int l_n = 0; l_n < 32; l_n++) {
    for (int l_k = 0; l_k < 32; l_k++) {
      for (int l_m = 0; l_m < 32; l_m++) {
        io_c[l_m + l_n * 32] += (i_a[l_m + l_k * 32] * i_b[l_k + l_n * 32]);
      }
    }
  }
}
