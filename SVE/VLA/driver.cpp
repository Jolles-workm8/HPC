#include <iostream>


extern "C" {

    void triad_low( uint64_t i_nValues,
                    float const * i_a,
                    float const * i_b,
                    float       * o_c);

}

void triad_high( uint64_t         i_nValues,
                 float    const * i_a,
                 float    const * i_b,
                 float          * o_c ) {
  for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
  }
}

int main( int i_argc, char const * i_argv[]){

    if(i_argc != 2) {
        std::cerr<<"error, run as ./a.out ID"<<std::endl;
    }

    int l_ex = atoi( i_argv[1]);

    float l_a[l_ex] = {0};
    float l_b[l_ex] = {0};
    float l_c_low[l_ex] = {0};
    float l_c_high[l_ex] = {0};

    for(size_t l_en=0; l_en<128; l_en++){
        l_dataIn[l_en]= (l_en+1)*2;
    }

    triad_high(l_ex, l_a, l_b, l_c_high);
    triad_low(l_ex, l_a, l_b, l_c_low);

    for(size_t i=0; i<64; i++){
      float error = abs(l_c_low[i] - l_c_high[i])
      if(error> 0.000001){
        std::cout << "wrong calculation of C in 19_4_4 " << l_c_low[i] << " "<< l_c_high<< "\n"
        exit( EXIT_FAILURE );
      }
    }

    return EXIT_SUCCESS;
}
