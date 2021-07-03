#include "SmallGEMM.h"

void (*mini_jit::generators::SmallGEMM::generate( uint32_t i_m,
                                                  uint32_t i_n,
                                                  uint32_t i_k))( float const * i_a,
                                                                  float const * i_b,
                                                                  float * io_c) {
  uint32_t l_ins = 0;

  if(i_m != 16 || i_n != 4 || i_k != 4){
    exit( EXIT_FAILURE );
  }


  mini_jit::instructions::Asimd::arrspec_t l_as = mini_jit::instructions::Asimd::arrspec_t::s4;
  //store
  // stp  d8,  d9, [sp, #-16]!
  m_kernel.addInstruction( 0x6DBF27E8);

  // stp  d10,  d11, [sp, #-16]!
  m_kernel.addInstruction( 0x6DBF2FEA );

  // stp  d12,  d13, [sp, #-16]!
  m_kernel.addInstruction( 0x6DBF37EC );

  // stp  d14,  d15, [sp, #-16]!
  m_kernel.addInstruction( 0x6DBF3FEE );


  //load Matrix C
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(0, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(2,2,16*4,0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(4, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(2,2,16*4,0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(8, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(2,2,16*4,0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(12, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpSubImm(2,2,16*4*3,0);
  m_kernel.addInstruction(l_ins);



  //load Matrix B
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(16, 1, l_as, 4);
  m_kernel.addInstruction(l_ins);




  //load first row of A
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(20, 0, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(0,0,16*4,0);
  m_kernel.addInstruction(l_ins);

  //calculate first row of A
  l_ins = instructions::Asimd::dpFmlaElement(0, 20, 16, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(1, 21, 16, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(2, 22, 16, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(3, 23, 16, l_as, 0);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(4, 20, 17, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(5, 21, 17, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(6, 22, 17, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(7, 23, 17, l_as, 0);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(8, 20, 18, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(9, 21, 18, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(10, 22, 18, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(11, 23, 18, l_as, 0);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(12, 20, 19, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(13, 21, 19, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(14, 22, 19, l_as, 0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(15, 23, 19, l_as, 0);
  m_kernel.addInstruction(l_ins);





  //load second row of A
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(20, 0, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(0,0,16*4,0);
  m_kernel.addInstruction(l_ins);

  //calculate second row of A
  l_ins = instructions::Asimd::dpFmlaElement(0, 20, 16, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(1, 21, 16, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(2, 22, 16, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(3, 23, 16, l_as, 1);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(4, 20, 17, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(5, 21, 17, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(6, 22, 17, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(7, 23, 17, l_as, 1);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(8, 20, 18, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(9, 21, 18, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(10, 22, 18, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(11, 23, 18, l_as, 1);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(12, 20, 19, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(13, 21, 19, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(14, 22, 19, l_as, 1);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(15, 23, 19, l_as, 1);
  m_kernel.addInstruction(l_ins);





  //load third row of A
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(20, 0, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(0,0,16*4,0);
  m_kernel.addInstruction(l_ins);

  //calculate second row of A
  l_ins = instructions::Asimd::dpFmlaElement(0, 20, 16, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(1, 21, 16, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(2, 22, 16, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(3, 23, 16, l_as, 2);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(4, 20, 17, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(5, 21, 17, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(6, 22, 17, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(7, 23, 17, l_as, 2);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(8, 20, 18, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(9, 21, 18, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(10, 22, 18, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(11, 23, 18, l_as, 2);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(12, 20, 19, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(13, 21, 19, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(14, 22, 19, l_as, 2);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(15, 23, 19, l_as, 2);
  m_kernel.addInstruction(l_ins);




  //load fourth row of A
  l_ins = instructions::Asimd::lsLd1MultipleNoOff(20, 0, l_as, 4);
  m_kernel.addInstruction(l_ins);
;

  //calculate second row of A
  l_ins = instructions::Asimd::dpFmlaElement(0, 20, 16, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(1, 21, 16, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(2, 22, 16, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(3, 23, 16, l_as, 3);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(4, 20, 17, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(5, 21, 17, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(6, 22, 17, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(7, 23, 17, l_as, 3);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(8, 20, 18, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(9, 21, 18, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(10, 22, 18, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(11, 23, 18, l_as, 3);
  m_kernel.addInstruction(l_ins);

  l_ins = instructions::Asimd::dpFmlaElement(12, 20, 19, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(13, 21, 19, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(14, 22, 19, l_as, 3);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::dpFmlaElement(15, 23, 19, l_as, 3);
  m_kernel.addInstruction(l_ins);



  //store C
  l_ins = instructions::Asimd::lsSt1MultipleNoOff(0, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(2,2,16*4,0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::lsSt1MultipleNoOff(4, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(2,2,16*4,0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::lsSt1MultipleNoOff(8, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Base::dpAddImm(2,2,16*4,0);
  m_kernel.addInstruction(l_ins);
  l_ins = instructions::Asimd::lsSt1MultipleNoOff(12, 2, l_as, 4);
  m_kernel.addInstruction(l_ins);



  //restore
  // ldp  d14,  d15, [sp, #-16]!
  m_kernel.addInstruction( 0x6DFF3FEE);

  // ldp  d12,  d13, [sp, #-16]!
  m_kernel.addInstruction( 0x6DFF37EC );

  // ldp  d10,  d11, [sp, #-16]!
  m_kernel.addInstruction( 0x6DFF2FEA );

  // ldp  d8,  d9, [sp, #-16]!
  m_kernel.addInstruction( 0x6DFF27E8 );

  // ret
  l_ins = instructions::Base::bRet();
  m_kernel.addInstruction(l_ins);

  // we might debug through file-io
  // std::string l_file = "SmallGEMM.bin";
  // m_kernel.write( l_file.c_str() );

  m_kernel.setKernel();

  return (void(*) (float const * i_a,
                  float const * i_b,
                  float       * io_c))m_kernel.getKernel();
}
