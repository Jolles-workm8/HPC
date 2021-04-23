#include <bitset>
#include <iostream>

int main(int argc, char const *argv[]) {
  unsigned char l_data1 = 1;
  std::cout << "l_data1: " << std::bitset<8>(l_data1) << '\n';

  unsigned char l_data2 = 255;
  std::cout << "l_data2: " << std::bitset<8>(l_data2) << '\n';

  unsigned char l_data3 = l_data2 + 1;
  std::cout << "l_data3: " << std::bitset<8>(l_data3) << '\n';

  unsigned char l_data4 = 0xA1;
  std::cout << "l_data4: " << std::bitset<8>(l_data4) << '\n';

  unsigned char l_data5 = 0b1001011;
  std::cout << "l_data5: " << std::bitset<8>(l_data5) << '\n';

  unsigned char l_data6 = 'H';
  std::cout << "l_data6: " << std::bitset<8>(l_data6) << '\n';

  char l_data7 = -4;
  std::cout << "l_data7: " << std::bitset<8>(l_data7) << '\n';

  unsigned int l_data8 = 1u << 11;
  std::cout << "l_data8: " << std::bitset<32>(l_data8) << '\n';

  unsigned int l_data9 = l_data8 << 21;
  std::cout << "l_data9: " << std::bitset<32>(l_data9) << '\n';

  unsigned int l_data10 = 0xFFFFFFFF >> 5;
  std::cout << "l_data10: " << std::bitset<32>(l_data10) << '\n';

  unsigned int l_data11 = 0b1001 ^ 0b01111;
  std::cout << "l_data11: " << std::bitset<32>(l_data11) << '\n';

  unsigned int l_data12 = ~0b1001;
  std::cout << "l_data12: " << std::bitset<32>(l_data12) << '\n';

  unsigned int l_data13 = 0xF0 & 0b1010101;
  std::cout << "l_data13: " << std::bitset<32>(l_data13) << '\n';

  unsigned int l_data14 = 0b001 | 0b101;
  std::cout << "l_data14: " << std::bitset<32>(l_data14) << '\n';

  unsigned int l_data15 = 7743;
  std::cout << "l_data15: " << std::bitset<32>(l_data15) << '\n';

  int l_data16 = -7743;
  std::cout << "l_data16: " << std::bitset<32>(l_data16) << '\n';

  return 0;
}
