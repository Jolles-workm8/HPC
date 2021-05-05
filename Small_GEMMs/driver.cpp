#include "gemm_ref.h"
#include <iostream>
#include <string>

void printMatr(std::string name, float const * i_x, unsigned int  i_m,
                unsigned int i_n, unsigned int i_ldx ){

  std::cout << name << ": " << std::endl;
  for(int i = 0; i < i_n; i++){
    for(int j = 0; j < i_m; j++){
      std::cout << i_x[j + i * i_ldx]<< "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main(int argc, char const *argv[]) {
  unsigned int l_lambda = 2;

  float *l_a = new float[l_lambda* l_lambda];
  float *l_b = new float[l_lambda * l_lambda];
  float *l_c = new float[l_lambda * l_lambda];

  for(unsigned int i = 0; i < l_lambda; i++){
    for(unsigned int j = 0; j < l_lambda; j++){
      unsigned int pos = j + i * l_lambda;
      l_a[pos] = pos;
      l_b[pos] = pos;
      l_c[pos] = pos;
    }
  }
  printMatr("A", l_a, l_lambda, l_lambda, l_lambda);
  printMatr("B", l_b, l_lambda, l_lambda, l_lambda);
  printMatr("C", l_c, l_lambda, l_lambda, l_lambda);

  gemm_ref(l_a, l_b, l_c, l_lambda, l_lambda,
            l_lambda, l_lambda, l_lambda,l_lambda);

  printMatr("Result", l_c, l_lambda, l_lambda, l_lambda);
  return 0;
}
