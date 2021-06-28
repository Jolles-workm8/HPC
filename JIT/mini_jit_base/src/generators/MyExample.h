#ifndef MINI_JIT_GENERATORS_MYEXAMPLE_H
#define MINI_JIT_GENERATORS_MYEXAMPLE_H

#include "../backend/Kernel.h"
#include "../instructions/Base.h"

namespace mini_jit {
namespace generators {
class MyExample;
}
} // namespace mini_jit

class mini_jit::generators::MyExample {
private:
  //! kernel backend
  backend::Kernel m_kernel;

public:
  /**
   * Generates a simple kernel which multiplies 2 by 5 and adds 4.
   *
   * @return function pointer to kernel.
   **/
  uint32_t (*generate())();
};

#endif
