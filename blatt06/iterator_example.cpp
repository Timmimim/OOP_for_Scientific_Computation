#include <iostream>

#include "../blatt03/matrix.h"
#include "csrmatrix.hh"
#include "matrix_iterator.hh"
#include "mv.hh"


int main(){
  /*
  Matrix m(3,3);
  for(auto [row_idx, cols] : rows(m)){
    for(auto [col_idx, value] : cols){
      std::cout << row_idx << " " << col_idx << ": " << value << std::endl;
    }
  }
  */
  CSRMatrix csr(3,3);
  csr.addCoefficient(0,1,.5);
  csr.addCoefficient(1,0, 2);
  csr.addCoefficient(1,2, 2);
  csr.addCoefficient(2,0,10);
  csr.addCoefficient(2,1, 1);
  csr.addCoefficient(2,2,10);

  Vector v ({1,2,3});

  std::cout << "multiply csr*v" << std::endl;
  Vector res = csr * v;

  std::cout << "mv-multication result: [" << res << "]" << std::endl;
}

