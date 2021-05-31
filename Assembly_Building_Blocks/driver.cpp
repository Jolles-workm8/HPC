#include <iostream>
#include <chrono>
#include <vector>
#include <cstdint>
#include <limits>



double measure_GFLOPs(double seconds, unsigned int l_m, unsigned int l_n,
                      unsigned int l_k, unsigned int l_count) {

  return (double)(2 * l_k * l_m * l_n * (double)l_count) / (seconds * 1000000000);
}

extern "C" {
    void gemm_asm_asimd_16_4_4(float const * i_a,
                 float const    * i_b,
                 float          * o_c);

    void gemm_asm_asimd_16_4_12(float const * i_a,
                 float const    * i_b,
                 float          * o_c);
}

int main(){

    float * l_a = new float[64];
    float * l_b = new float[16];
    float * l_c = new float[64];

    unsigned int l_count = 100000000;

    //init the matrices
    for(size_t i=0; i<64; i++){
        l_a[i]=i;
        l_c[i]=1;
    }

    for(size_t i=0; i<16; i++){
        l_b[i]= i;
    }

    gemm_asm_asimd_16_4_4(l_a, l_b, l_c);

    for(size_t i=0; i<16; i++){
	std::cout << " | ";
	for(size_t j=0; j<4; j++){
	    std::cout<< l_c[j*16+i] << " | ";
	}
        std::cout << "\n";

    }
    std::cout<< std::endl << std::endl;


    using namespace std::chrono;

    auto start = system_clock::now();
    //execute the kernel l_count times
    for(size_t i =0; i< l_count; i++){
        gemm_asm_asimd_16_4_4(l_a, l_b, l_c);
    }

    auto end = system_clock::now();


    double seconds = duration<double>(end - start).count();

    double gflops = measure_GFLOPs(seconds, 16, 4, 4, l_count);

    std::cout << "Time: " << seconds << '\n'
        << "Executions: " << l_count << '\n'
        << "GFLOPs: " << gflops << '\n'
        << "Peak %: " << gflops/40.0 << '\n';



    delete[] l_a;
    delete[] l_b;
    delete[] l_c;

    //test 16 4 12
    float * l_a = new float[192];
    float * l_b = new float[48];
    float * l_c = new float[192];

    unsigned int l_count = 10000000;

    //init the matrices
    for(size_t i=0; i<64; i++){
        l_a[i]=i;
        l_c[i]=1;
    }

    for(size_t i=0; i<16; i++){
        l_b[i]= i;
    }

    gemm_asm_asimd_16_4_12(l_a, l_b, l_c);

    for(size_t i=0; i<16; i++){
	std::cout << " | ";
	for(size_t j=0; j<12; j++){
	    std::cout<< l_c[j*16+i] << " | ";
	}
        std::cout << "\n";

    }
    std::cout<< std::endl << std::endl;


    using namespace std::chrono;

    auto start = system_clock::now();
    //execute the kernel l_count times
    for(size_t i =0; i< l_count; i++){
        gemm_asm_asimd_16_4_4(l_a, l_b, l_c);
    }

    auto end = system_clock::now();


    double seconds = duration<double>(end - start).count();

    double gflops = measure_GFLOPs(seconds, 16, 4, 4, l_count);

    std::cout << "Time: " << seconds << '\n'
        << "Executions: " << l_count << '\n'
        << "GFLOPs: " << gflops << '\n'
        << "Peak %: " << gflops/40.0 << '\n';



    delete[] l_a;
    delete[] l_b;
    delete[] l_c;


    return EXIT_SUCCESS;
}
