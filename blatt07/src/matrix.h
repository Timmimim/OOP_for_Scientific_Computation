#pragma once

#include "vector.h"
#include <cassert>
#include <iostream>

class Matrix{
  std::vector<double> _data;
  unsigned int _cols;
  unsigned int _rows;
public:
  Matrix() = default;

  Matrix(const std::vector<std::vector<double>>& entries)
    : _data(entries.size() * entries[0].size()),
      _cols(entries[0].size()),
      _rows(entries.size()) 
  {  
    for (auto &&row : entries)
      assert(row.size() == entries[0].size());
        
    for(unsigned int i=0;i<_rows; ++i)
      for(unsigned int j=0;j<_cols; ++j)
        (*this)(i, j) = entries[i][j];
  }

  Matrix(unsigned int rows, unsigned int cols)
    : _data(rows*cols)
    , _cols(cols)
    , _rows(rows)
  {}

  double& operator()(unsigned int i, unsigned int j){
    return _data[i*_rows + j];
  }

  const double& operator()(unsigned int i, unsigned int j) const{
    return _data[i*_rows + j];
  }

  Matrix& operator=(const double& a){
    _data.assign(_rows*_cols, a);
    return *this;
  }

  unsigned int rows() const{
    return _rows;
  }

  unsigned int cols() const{
    return _cols;
  }

  void mv(const Vector& x, Vector& y) const {
    assert(x.size() == cols());
    assert(y.size() == rows());
    for(unsigned int i=0; i<rows(); ++i){
      y(i) = 0.0;
      for(unsigned int j=0; j<cols();++j){
        y(i) += (*this)(i,j)*x(j);
      }
    }
  }

  Vector operator*(const Vector& x) const {
    assert(x.size() == cols());
    Vector y(rows());
    y = 0.;
    this->mv(x, y);
    return y;
  }
};

std::ostream& operator <<(std::ostream& str, const Matrix& m){
  if(m.rows() == 0 || m.cols() == 0){
    str << "Matrix of size 0";
    return str;
  }
  str << "[";
  for(size_t i = 0; i < m.rows()-1; ++i)
  {
    str << "\t[" << m(i,0);
    for(size_t j=1; j < m.cols(); ++j){
      str << ", " << m(i,j);
    }
    str << "]\n";
  }
  str << "\t[" << m(m.rows()-1,0);
  for(size_t j=1; j < m.cols(); ++j){
    str << ", " << m(m.rows()-1,j);
  }
  str << "]";
  str << " ]";
  return str;
}