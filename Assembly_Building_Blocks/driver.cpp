#include <iostream>
#include <chrono>
#include <vector>
#include <cstdint>
#include <limits>
#include <stdlib.h>

void gemm_ref(float const *i_a, float const *i_b, float *io_c, unsigned int i_m,
              unsigned int i_n, unsigned int i_k, unsigned int i_lda,
              unsigned int i_ldb, unsigned int i_ldc) {

  for (int l_m = 0; l_m < i_m; l_m++) {
    for (int l_n = 0; l_n < i_n; l_n++) {
      for (int l_k = 0; l_k < i_k; l_k++) {
        io_c[l_m + l_n * i_ldc] +=
            (i_a[l_m + l_k * i_lda] * i_b[l_k + l_n * i_ldb]);
      }
    }
  }
}

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

    float * l_a_test = new float[64];
    float * l_b_test = new float[16];
    float * l_c_test = new float[64];

    unsigned int l_count = 100000000;

    //init the matrices
    for(size_t i=0; i<64; i++){
        l_a[i]=(float)i;
        l_c[i]=1.0f;

        l_a_test[i]=(float)i;
        l_c_test[i]=1.0f;
    }

    for(size_t i=0; i<16; i++){
        l_b[i]= (float)i;
        l_b_test[i]=(float)i;
    }
 
    gemm_asm_asimd_16_4_4(l_a, l_b, l_c);

    gemm_ref(l_a_test, l_b_test, l_c_test, 16, 4, 4, 16, 4, 16);

    //test if code is right, took therefor the reference function from previous lecture
    for(size_t i=0; i<64; i++){
        if(l_c[i] != l_c_test[i]){
         std::cout << "wrong calculation of C in 16_4_4 " << l_c[i] << " "<< l_c_test[i] << '\n';
         exit( EXIT_FAILURE );
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



    delete[] l_a;
    delete[] l_b;
    delete[] l_c;

    delete[] l_a_test;
    delete[] l_b_test;
    delete[] l_c_test;

    l_a = new float[192];
    l_b = new float[48];
    l_c = new float[64];

    l_a_test = new float[192];
    l_b_test = new float[48];
    l_c_test = new float[64];


    //init the matrices
    for(size_t i=0; i<192; i++){
        l_a[i]=(float)i;
        l_a_test[i]=(float)i;
    }

    for(size_t i=0; i<64, i++){
        l_c[i]=1.0f;
        l_c_test[i]=1.0f;
    }

    for(size_t i=0; i<48; i++){
        l_b[i]= (float)i;
        l_b_test[i] = (float)i;
    }


    gemm_asm_asimd_16_4_12(l_a, l_b, l_c);

    gemm_ref(l_a_test, l_b_test, l_c_test, 16, 4, 12, 16, 12, 16);



    for(size_t i=0; i<64; i++){
        if(l_c[i] != l_c_test[i]){
         std::cout << "wrong calculation of C in 16_4_12 "<<i<<" "<< l_c[i] << " "<< l_c_test[i] << '\n';
         exit( EXIT_FAILURE );
        }
    }


    start = system_clock::now();
    //execute the kernel l_count times
    for(size_t i =0; i< l_count; i++){
        gemm_asm_asimd_16_4_12(l_a, l_b, l_c);
    }

    end = system_clock::now();


    seconds = duration<double>(end - start).count();

    gflops = measure_GFLOPs(seconds, 16, 4, 12, l_count);

    std::cout << "Time: " << seconds << '\n'
        << "Executions: " << l_count << '\n'
        << "GFLOPs: " << gflops << '\n'
        << "Peak %: " << gflops/40.0 << '\n';


  //  delete[] l_a;
 //   delete[] l_b;
//    delete[] l_c;
//    delete[] l_a_test;
//    delete[] l_b_test;
//    delete[] l_c_test;

    return EXIT_SUCCESS;
}
