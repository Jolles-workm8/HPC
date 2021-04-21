#include <bitset>
#include <iostream>

int main(int argc, char const *argv[]) {
  unsigned char l_data1 = 1;
  std::bitset<8> x(l_data1);
  std::cout << "l_data1:" << x << '\n';

  unsigned char l_data2 = 255;
  std::bitset<8> y(l_data2);
  std::cout << "l_data2:" << y << '\n';

  unsigned char l_data3 = l_data2 + 1;
  std::bitset<8> z(l_data3);
  std::cout << "l_data3:" << z << '\n';

  unsigned char l_data4 = 0xA1;
  unsigned char l_data5 = 0b1001011;
  unsigned char l_data6 = 'H';
  char l_data7 = -4;
  unsigned int l_data8 = 1u << 11;
  unsigned int l_data9 = l_data8 << 21;
  unsigned int l_data10 = 0xFFFFFFFF >> 5;
  unsigned int l_data11 = 0b1001 ^ 0b01111;
  unsigned int l_data12 = ~0b1001;
  unsigned int l_data13 = 0xF0 & 0b1010101;
  unsigned int l_data14 = 0b001 | 0b101;
  unsigned int l_data15 = 7743;
  int l_data16 = -7743;

  return 0;
}
