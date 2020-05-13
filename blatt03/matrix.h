#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class Matrix{
public:
  Matrix(unsigned int rows, unsigned int cols) 
    : _rows(rows), _cols(cols), _data(rows, std::vector<double>(cols,0)) {}
    
  // square matrix constructor
  Matrix(unsigned int dim) 
    : _rows(dim), _cols(dim), _data(dim, std::vector<double>(dim,0)) {}

  // construct from existing 'free' data
  Matrix(std::vector<std::vector<double>>&& data){
    _data = data;
    _rows = data.size();
    _cols = data[0].size();
    data.erase(data.begin(), data.end());
  }

  // destructor
  ~Matrix() {}

  // copy constructor
  Matrix(const Matrix& other)
  {
    _rows = other.rows();
    _cols = other.cols();
    _data = other._data;
  }

  // move constructor
  Matrix(Matrix&& other)
  {
    _rows = other.rows();
    _cols = other.cols();
    _data = other._data;
    other._data.erase(other._data.begin(),other._data.end());
    other._rows = 0;
    other._cols = 0;
  }
  // assignment constructor
  Matrix& operator= (const Matrix& other)
  {
    if (this == &other) return *this;
    _data = other._data;
    _rows = other.rows();
    _cols = other.cols();
    return *this;
  }

  // move assignment constructor
  Matrix& operator= (Matrix&& other)
  {
    if (this == &other) return *this;
    _rows = other.rows();
    _cols = other.cols();
    _data = other._data;
    other._data.erase(other._data.begin(),other._data.end());
    other._rows = 0;
    other._cols = 0;
    return *this;
  }

  double& operator()(unsigned int i, unsigned int j){
    assert(i < _rows && j < _cols);
    return _data[i][j];
  }

  const double& operator()(unsigned int i, unsigned int j) const{
    assert(i < _rows && j < _cols);
    return _data[i][j];
  }

  Matrix operator* (const Matrix& other)
  {
    assert(_cols == other.rows());
    Matrix result(_rows, other.cols());

    for(size_t i=0 ; i<_rows ; i++)
    {
      for(size_t j=0 ; j<other.cols(); j++) 
      {
        // result(i,j) initialized to 0 by default, see constructor
        for(size_t k=0 ; k<_cols ; k++)  
        {
            result(i,j) += _data[i][k] * other(k,j);
        }
      }
    }
    return result;
  }

  unsigned int rows() const{
    return _rows;
  }

  unsigned int cols() const{
    return _cols;
  }

  Matrix transpose() const
  {
    Matrix result(*this);
    for (size_t row = 0; row < _rows; ++row) {
      for (size_t col = 0; col < row; ++col) {
        double temp = _data[row][col];
        result._data[row][col] = _data[col][row];
        result._data[col][row] = temp;
      }
    }
    return result;
  }

  void mv(const Vector& x, Vector& y) const{
    assert(_rows == y.size());
    assert(_cols == x.size());
    for (size_t row = 0; row < _rows; ++row)
    {
      double step_result=0.;
      for (size_t col = 0; col < _cols; ++col)
        step_result += _data[row][col] * x(col);
      y(row) = step_result;
    }
  }


private:
  unsigned int _rows;
  unsigned int _cols;
  std::vector<std::vector<double>> _data;

};

#endif
