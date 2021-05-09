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

double measure_GFLOPs(double seconds, unsigned int l_m, unsigned int l_n,
                      unsigned int l_k, unsigned int l_count) {

  return (double)(2 * l_k * l_m * l_n * l_count) / (seconds * 1000000000);
}

int main(int argc, char const *argv[]) {
  unsigned int l_m = 32;
  unsigned int l_n = 32;
  unsigned int l_k = 32;

  // To simplify things we assumed that the leading dimension was equal to the
  // number of columns.
  unsigned int l_lda = l_m;
  unsigned int l_ldb = l_k;
  unsigned int l_ldc = l_m;

  std::vector<float> l_a(l_m * l_k);
  std::vector<float> l_b(l_n * l_k);
  std::vector<float> l_c(l_m * l_n);

  // to increase use iota
  std::fill(l_a.begin(), l_a.end(), 1);
  std::fill(l_b.begin(), l_b.end(), 1);
  std::fill(l_c.begin(), l_c.end(), 0);

  // printMatr("A", l_a.data(), l_m, l_k, l_lda);
  // printMatr("B", l_b.data(), l_n, l_k, l_ldb);
  // printMatr("C", l_c.data(), l_m, l_n, l_ldc);

  unsigned int l_count = 5000;

  using namespace std::chrono;

  auto start = system_clock::now();

  for (size_t i = 0; i < l_count; i++) {
    gemm_ref(l_a.data(), l_b.data(), l_c.data(), l_m, l_n, l_k, l_lda, l_ldb,
             l_ldc);
  }

  auto end = system_clock::now();

  double seconds = duration<double>(end - start).count();

  // printMatr("Result", l_c.data(), l_m, l_n, l_ldc);

  std::cout << "Time:" << seconds << '\n';
  std::cout << "GFLOP's: " << measure_GFLOPs(seconds, l_m, l_k, l_n, l_count)
            << '\n';

  return 0;
}
