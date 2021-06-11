#include <iostream>

extern "C" {

    void sve_load_store( uint32_t * l_dataIn, uint32_t * l_dataOut);
    void sve_predicated_load_store( uint32_t * l_dataIn, uint32_t * l_dataOut);
    void sve_predicated_argument_load_store( uint32_t * l_dataIn, uint32_t * l_dataOut);
    void sve_mul_load_store(uint32_t * l_dataIn, uint32_t * l_dataOut);
}



int main( int i_argc, char const * i_argv[]){

    if(i_argc != 2) {
        std::cerr<<"error, run as ./a.out ID"<<std::endl;
    }

    uint32_t l_dataIn[128] = {0};
    uint32_t l_dataOut[128] = {0};

    for(size_t l_en=0; l_en<128; l_en++){
        l_dataIn[l_en]= (l_en+1)*2;
    }

    int l_ex = atoi( i_argv[1]);

    if(l_ex == 0) {
        sve_load_store(l_dataIn, l_dataOut);
    }else if(l_ex == 1){
        sve_predicated_load_store(l_dataIn, l_dataOut);
    }else if(l_ex == 2) {
        sve_predicated_argument_load_store(l_dataIn, l_dataOut);
    }else if(l_ex == 3) {
        sve_mul_load_store(l_dataIn, l_dataOut);
    }
    //for better opverview in the terminal we commented this section. Can be uncommented if contents of the particular arrays are of interest.
    /*
    if( l_ex <4 ||l_ex ==6){
        for(size_t l_en = 0; l_en <16; l_en ++){
            std::cout<< "en / in / out : " << l_en << '\t' << l_dataIn[l_en]<< '\t' << l_dataOut[l_en] << std::endl; 
        }
    }
*/
    return EXIT_SUCCESS;
}