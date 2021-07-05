#include "generators/Loop.h"
#include "generators/MyExample.h"
#include "generators/Simple.h"
#include "generators/SmallGEMM.h"
#include <iostream>
#include <chrono>

double measure_GFLOPs(double seconds, unsigned int l_m, unsigned int l_n,
                      unsigned int l_k, unsigned int l_count) {

  return (double)(2 * l_k * l_m * l_n * (double)l_count) / (seconds * 1000000000);
}

int main() {
  std::cout << "###########################" << std::endl;
  std::cout << "### welcome to mini_jit ###" << std::endl;
  std::cout << "###########################" << std::endl;

  std::cout << "simple:" << std::endl;
  std::cout << "  generating simple kernel" << std::endl;
  mini_jit::generators::Simple l_simple;
  uint32_t (*l_funcSimple)() = l_simple.generate();

  std::cout << "  running" << std::endl;
  std::cout << "    result: " << l_funcSimple() << std::endl;

  std::cout << "loop:" << std::endl;
  std::cout << "  generating" << std::endl;
  mini_jit::generators::Loop l_loop;
  uint32_t (*l_funcLoop)() = l_loop.generate(32);

  std::cout << "  running" << std::endl;
  std::cout << "    result: " << l_funcLoop() << std::endl;

  std::cout << "MyExample:" << std::endl;
  std::cout << "  generating" << std::endl;
  mini_jit::generators::MyExample l_myexample;
  uint32_t (*l_funcMyExample)() = l_myexample.generate();

  std::cout << "  running" << std::endl;
  std::cout << "    result: " << l_funcMyExample() << std::endl;

  float l_a[64];
  float l_b[16];
  float l_c[64];

  unsigned int l_count = 100000000;

  for( size_t i =0; i<64; i++){
    l_a[i] = 1;
    l_c[i] = 0;
    if(i<16){
      l_b[i] = 1;
    }
  }

  std::cout << "small GEMM" << std::endl;
  std::cout << "  generating" << std::endl;
  mini_jit::generators::SmallGEMM l_smallGEMM;
  void (*l_funcsmallGEMM)(float const *, float const *, float *) = l_smallGEMM.generate(16, 4, 4);

  std::cout << "  running" << std::endl;

  using namespace std::chrono;

  auto start = system_clock::now();
  for(size_t i =0; i< l_count; i++){
  l_funcsmallGEMM(l_a, l_b, l_c);
  }
  auto end = system_clock::now();


  double seconds = duration<double>(end - start).count();

    double gflops = measure_GFLOPs(seconds, 16, 4, 4, l_count);

    std::cout << "Time: " << seconds << '\n'
        << "Executions: " << l_count << '\n'
        << "GFLOPs: " << gflops << '\n'
        << "Peak %: " << gflops/40.0 << '\n';

std::cout << std::endl;

std::cout << " Code took " << seconds << " seconds" << std::endl;
  
  std::cout << "##############################" << std::endl;
  std::cout << "### mini_jit says bye, bye ###" << std::endl;
  std::cout << "##############################" << std::endl;


  return EXIT_SUCCESS;
}
