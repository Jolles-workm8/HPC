#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "gemm_compiler_32_32_32_32_32_32.hpp"
#include "gemm_ref.hpp"

TEST_CASE("gemm_ref") {
  int constexpr n = 32;
  int constexpr m = 32;
  int constexpr k = 32;

  int lda = m;
  int ldb = n;
  int ldc = k;

  std::vector<float> a(n * m, 0);
  std::vector<float> b(n * k, 1);
  std::vector<float> c(m * k, 0);

  gemm_ref(a.data(), b.data(), c.data(), m, n, k, lda, ldb, ldc);

  for (size_t i = 1; i < c.size(); i++) {
    REQUIRE((c[i] == 0 == true));
  }

  std::fill(a.begin(), a.end(), 1);
  std::fill(b.begin(), b.end(), 1);

  gemm_ref(a.data(), b.data(), c.data(), m, n, k, lda, ldb, ldc);

  for (size_t i = 1; i < c.size(); i++) {
    REQUIRE(c[i] == 32);
  }

  gemm_ref(a.data(), b.data(), c.data(), m, n, k, lda, ldb, ldc);

  for (size_t i = 1; i < c.size(); i++) {
    REQUIRE(c[i] == 64);
  }

  std::fill(a.begin(), a.end(), -1);

  gemm_ref(a.data(), b.data(), c.data(), m, n, k, lda, ldb, ldc);

  for (size_t i = 1; i < c.size(); i++) {
    REQUIRE(c[i] == 32);
  }
}

TEST_CASE("Comparison") {
  int constexpr n = 32;
  int constexpr m = 32;
  int constexpr k = 32;

  int lda = m;
  int ldb = n;
  int ldc = k;

  std::vector<float> a_ref(n * m, 0);
  std::vector<float> b_ref(n * k, 0);
  std::vector<float> c_ref(m * k, 0);

  std::iota(a_ref.begin(), a_ref.end(), 0.3);
  std::iota(b_ref.begin(), b_ref.end(), 0.3);

  gemm_ref(a_ref.data(), b_ref.data(), c_ref.data(), m, n, k, lda, ldb, ldc);

  std::vector<float> a0(n * m, 0);
  std::vector<float> b0(n * k, 0);
  std::vector<float> c0(k * m, 0);

  std::iota(a0.begin(), a0.end(), 0.3);
  std::iota(b0.begin(), b0.end(), 0.3);

  gemm_compiler_32_32_32_32_32_32_mnk(a0.data(), b0.data(), c0.data());

  for (size_t i = 1; i < c_ref.size(); i++) {
    REQUIRE(c_ref[i] == c0[i]);
  }

  std::vector<float> a1(n * m, 0);
  std::vector<float> b1(n * k, 0);
  std::vector<float> c1(k * m, 0);

  std::iota(a1.begin(), a1.end(), 0.3);
  std::iota(b1.begin(), b1.end(), 0.3);

  gemm_compiler_32_32_32_32_32_32_nkm(a1.data(), b1.data(), c1.data());

  for (size_t i = 1; i < c_ref.size(); i++) {
    REQUIRE(c_ref[i] == c1[i]);
  }
}
