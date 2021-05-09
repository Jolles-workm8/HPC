#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
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
    REQUIRE((c[i] == 32 == true));
  }

  gemm_ref(a.data(), b.data(), c.data(), m, n, k, lda, ldb, ldc);

  for (size_t i = 1; i < c.size(); i++) {
    REQUIRE((c[i] == 64 == true));
  }

  std::fill(a.begin(), a.end(), -1);

  gemm_ref(a.data(), b.data(), c.data(), m, n, k, lda, ldb, ldc);

  for (size_t i = 1; i < c.size(); i++) {
    REQUIRE((c[i] == 32 == true));
  }
}
