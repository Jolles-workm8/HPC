#include <bitset>
#include <iostream>




unsigned int instruction_asimd_compute( unsigned int  i_vec_instr,
                                        unsigned char i_vec_reg_dst,
                                        unsigned char i_vec_reg_src_0,
                                        unsigned char i_vec_reg_src_1 ){


  //cast tounsigned int
  unsigned int l_dst = (unsigned int) i_vec_reg_dst;
  unsigned int l_src_0 = (unsigned int) i_vec_reg_src_0;
  unsigned int l_src_1 = (unsigned int) i_vec_reg_src_1;

  //mask to ge bits 0-4
  unsigned int l_mask = 0b11111;
  l_dst = l_dst & l_mask;
  l_src_0 = l_src_0 & l_mask;
  l_src_1 = l_src_1 & l_mask;

  //move Bits to right position with shift
  l_src_0 = l_src_0 << 5;
  l_src_1 = l_src_1 << 16;

  //combine all values
  unsigned int l_instr = i_vec_instr |  l_dst | l_src_0 | l_src_1;
  return l_instr;

}

int main(int argc, char const *argv[]) {

  unsigned int  l_vec_instr = 0b01001110001000001100110000000000;
  unsigned char l_vec_reg_dst = 0b00000000;
  unsigned char l_vec_reg_src_0 = 0b00000001;
  unsigned char l_vec_reg_src_1 = 0b00000010;
  unsigned int l_ret;

  l_ret = instruction_asimd_compute(l_vec_instr, l_vec_reg_dst, l_vec_reg_src_0 ,l_vec_reg_src_1);

  std::bitset<32> x(l_ret);
  std::cout << "l_ret:" << x << std::endl;

}
