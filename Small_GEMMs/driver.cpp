#include "gemm_ref.hpp"
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>

void printMatr(std::string name, float const *i_x, unsigned int i_m,
               unsigned int i_n, unsigned int i_ldx) {

  std::cout << name << ": " << std::endl;
  for (int i = 0; i < i_n; i++) {
    for (int j = 0; j < i_m; j++) {
      std::cout << i_x[j + i * i_ldx] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main(int argc, char const *argv[]) {
  unsigned int l_m = 2;
  unsigned int l_n = 2;
  unsigned int l_k = 2;

  // To simplify things we assumed that the leading dimension was equal to the
  // number of columns.
  unsigned int l_lda = l_m;
  unsigned int l_ldb = l_k;
  unsigned int l_ldc = l_m;

  std::vector<float> l_a(l_m * l_k);
  std::vector<float> l_b(l_n * l_k);
  std::vector<float> l_c(l_m * l_n);

  std::iota(l_a.begin(), l_a.end(), 0);
  std::iota(l_b.begin(), l_b.end(), 0);
  std::fill(l_c.begin(), l_c.end(), 0);

  printMatr("A", l_a.data(), l_m, l_k, l_lda);
  printMatr("B", l_b.data(), l_n, l_k, l_ldb);
  printMatr("C", l_c.data(), l_m, l_n, l_ldc);

  using namespace std::chrono;

  auto start = system_clock::now();

  gemm_ref(l_a.data(), l_b.data(), l_c.data(), l_m, l_n, l_k, l_lda, l_ldb,
           l_ldc);

  auto end = system_clock::now();

  double seconds = duration<double>(end - start).count();

  std::cout << "time needed was:" << seconds << '\n';
  printMatr("Result", l_c.data(), l_m, l_n, l_ldc);
  return 0;
}
