#ifndef MINI_JIT_GENERATORS_Small_GEMM_H
#define MINI_JIT_GENERATORS_Small_GEMM_H

#include "../backend/Kernel.h"
#include "../instructions/Base.h"
#include "../instructions/Asimd.h"

namespace mini_jit {
namespace generators {
class SmallGEMM;
}
} // namespace mini_jit

class mini_jit::generators::SmallGEMM {
private:
  //! kernel backend
  backend::Kernel m_kernel;

public:
  /**
   * Todo: Doku
   **/
  void (*generate(  uint32_t i_m,
                    uint32_t i_n,
                    uint32_t i_k))( float const * i_a,
                                    float const * i_b,
                                    float       * io_c);
};

#endif
