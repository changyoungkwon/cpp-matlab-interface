#include <iostream>
#include "libmrxg.h"
#include "matrix.h"

int main(){
  // initalize library
  if( !libmrxgInitialize() ){
    std::cerr << "Error in initializing libmrxg" << std::endl;
    return -1;
  }

  mwArray filename("flair.dat");
  mwArray rawd;
  mwArray im_mask;
  mwArray k_mask;
  mwArray k_norm;
  mwArray header;

  mrxg_pre(5, rawd, im_mask, k_mask, k_norm, header, filename);
  std::cout << header << std::endl;
  // terminate
  libmrxgTerminate();
}
