#include <iostream>
#include "libmrxg.h"
#include "matrix.h"
#include <time.h>

int main(int argc, char** argv){
  // initalize library
  struct timespec start;
  clock_gettime( CLOCK_MONOTONIC, &start);
  if( !libmrxgInitialize() ){
    std::cerr << "Error in initializing libmrxg" << std::endl;
    return -1;
  }

  mwArray filename(argv[1]);
  mwArray eigen;
  mwArray rawd;
  mwArray im_mask;
  mwArray k_mask;
  mwArray k_norm;
  mwArray recon_option;
  mwArray header;

  mrxg_pre(5, rawd, im_mask, k_mask, k_norm, header, recon_option, filename);
  std::cout << header << std::endl;
  // terminate
  libmrxgTerminate();
  struct timespec end;
  clock_gettime( CLOCK_MONOTONIC, &end);
  std::cout << "time spent : " << end.tv_sec - start.tv_sec << "s" << std::endl;
  return 0;
}
