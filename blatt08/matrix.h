#pragma once

#include <vector>
#include <cassert>

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
};
