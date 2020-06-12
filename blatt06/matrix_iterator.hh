#ifndef MATRIX_ITERATOR_H
#define MATRIX_ITERATOR_H

#include "../blatt03/matrix.h"
#include "csrmatrix.h"

class MatrixColIterator {
  Matrix& _matrix;
  unsigned int _row;
  unsigned int _col;
public:
  MatrixColIterator(Matrix& m, unsigned int row, unsigned int col)
    : _matrix(m)
    , _row(row)
    , _col(col)
  {}

  bool operator==(const MatrixColIterator& other) const{
    return _row==other._row && _col == other._col;
  }

  bool operator!=(const MatrixColIterator& other) const{
    return !((*this)==other);
  }

  MatrixColIterator& operator++(){
    _col++;
    return *this;
  }

  std::pair<unsigned int, double&> operator*(){
    return {_col, _matrix(_row, _col)};
  }

  std::pair<unsigned int, double&> operator->(){
    return *(*this);
  }
};

class MatrixColRange {
  Matrix& _matrix;
  unsigned int _row;
public:
  MatrixColRange(Matrix& m, unsigned int row)
    : _matrix(m)
    , _row(row)
  {}

  MatrixColIterator begin(){
    return {_matrix, _row, 0};
  }

  MatrixColIterator end(){
    return {_matrix, _row, _matrix.cols()};
  }
};

class MatrixRowIterator {
  Matrix& _matrix;
  unsigned int _row;
public:
  MatrixRowIterator(Matrix& m, unsigned int row)
    : _matrix(m)
    , _row(row)
  {}

  bool operator==(const MatrixRowIterator& other) const{
    return _row==other._row;
  }

  bool operator!=(const MatrixRowIterator& other) const{
    return !((*this)==other);
  }

  MatrixRowIterator& operator++(){
    _row++;
    return *this;
  }

  std::pair<unsigned int, MatrixColRange> operator*() const{
    return {_row, MatrixColRange(_matrix, _row)};
  }

  std::pair<unsigned int, MatrixColRange> operator->() const{
    return *(*this);
  }
};

class MatrixRowRange{
  Matrix& _matrix;
public:
  MatrixRowRange(Matrix& m)
    : _matrix(m)
  {}

  MatrixRowIterator begin(){
    return {_matrix, 0};
  }

  MatrixRowIterator end(){
    return {_matrix, _matrix.rows()};
  }
};

MatrixRowRange rows(Matrix& m){
  return m;
}

auto rows(const CSRMatrix& m){
  // TODO: implement me!
}

#endif
