#include <stdint.h>


void copy_c(uint32_t * l_a, uint64_t *l_b){
  for(int i; i<7; i++){
      l_b[i] = (uint64_t)l_a[i];
  }
}
