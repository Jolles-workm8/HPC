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
}

int main(){
    
    float * l_a = new float[64];
    float * l_b = new float[16];
    float * l_c = new float[64];

    unsigned int l_count = 100000000;

    //init the matrices
    for(size_t i=0; i<64; i++){
        l_a[i]=(float)i;
        l_c[i]=0.0f;
    }

    for(size_t i=0; i<16; i++){
        if(i == 0 || i == 5 || i == 10 || i ==15){
            l_b[i]=1.0f;
            }
        else{
            l_b[i]=0.0f;
        }
    }
    
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
    
    std::cout << "unsigned float limits: " << std::numeric_limits<float>::max() << '\n';

    for(size_t i=0; i<64; i++){
        if(i%4 ==0 ){
            std::cout << "\n" << " | ";
        }
        std::cout<< l_c[i] << " | ";       
    }
    std::cout<< std::endl << std::endl;

    delete[] l_a;
    delete[] l_b;
    delete[] l_c;


    return EXIT_SUCCESS;
}