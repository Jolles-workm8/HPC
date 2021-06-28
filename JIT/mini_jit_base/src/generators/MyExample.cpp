#include "MyExample.h"

uint32_t (*mini_jit::generators::MyExample::generate())() {
  uint32_t l_ins = 0;

  // mov w0, #0x4
  l_ins = instructions::Base::dpMovImm(0, 4, 0);
  m_kernel.addInstruction(l_ins);

  // mov w1, #0x5
  l_ins = instructions::Base::dpMovImm(1, 5, 0);
  m_kernel.addInstruction(l_ins);

  // mov w2, #0x2
  l_ins = instructions::Base::dpMovImm(2, 2, 0);
  m_kernel.addInstruction(l_ins);

  // madd w0, w1, w2, w0
  l_ins = instructions::Base::dpMAdd(0, 1, 2, 0, 0);
  m_kernel.addInstruction(l_ins);

  // ret
  l_ins = instructions::Base::bRet();
  m_kernel.addInstruction(l_ins);

  // we might debug through file-io
  // std::string l_file = "myexample.bin";
  // m_kernel.write( l_file.c_str() );

  m_kernel.setKernel();

  return (uint32_t(*)())m_kernel.getKernel();
}
