#ifndef LU_H
#define LU_H

#inlcude "vector.h"
#include "matrix.h"

class LU{
  Matrix _decomposition; // store the decomposition in this matrix
public:
  // decomposing the Matrix m, without modifing it
  void decompose(const Matrix& m){
    // TODO: implement me!
  }

  // decompose the Matrix m, reuse its resources
  void decompose(Matrix&& m){

  }

  void solve(const Vector& b, Vector& x){
    // TODO: implement me!
  }
};

#endif
