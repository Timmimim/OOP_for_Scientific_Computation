#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class Matrix{
public:
  Matrix(unsigned int rows, unsigned int cols)
  {
    // TODO: implement me!
  }

  double& operator()(unisgned int i, unsigned int j){
    // TODO: implement me!
  }

  const double& operator()(unisgned int i, unsigned int j) const{
    // TODO: implement me!
  }

  unsigned int rows() const{
    // TODO: implement me!
  }

  unsigned int cols() const{
    // TODO: implement me!
  }

  void mv(const Vector& x, Vector& y) const{
    // TODO: implement me!
  }
};

#endif
