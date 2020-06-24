#ifndef MATRIX_ITERATOR_H
#define MATRIX_ITERATOR_H

#include "../../blatt03/matrix.h"
#include "csrmatrix.hh"

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

// ===================================================== //
///////////////////////////////////////////////////////////
//        CSR Matrix Iterator / Range Classes            //
///////////////////////////////////////////////////////////
// ===================================================== //

class CSRMatrixColIterator {
  CSRMatrix& _matrix;
  unsigned int _row;
  unsigned int _coeff_idx;
public:
  CSRMatrixColIterator(CSRMatrix& m, unsigned int coeff_idx)
    : _matrix(m)
    , _coeff_idx(coeff_idx)
  {}

  bool operator==(const CSRMatrixColIterator& other) const{
    return _coeff_idx == other._coeff_idx;
  }

  bool operator!=(const CSRMatrixColIterator& other) const{
    return !((*this)==other);
  }

  CSRMatrixColIterator& operator++(){
    _coeff_idx++;
    return *this;
  }

  std::pair<unsigned int, double&> operator*(){
    /*  // To iterate over all theorertical values between first and last in row, use this;
    double val = 0.;
    for(int i = _matrix._rowStarts[_row]; i < _matrix._rowStarts[_row + 1]; ++i)
        if (_matrix._colIndices[i] == _col)
            val = _matrix._coefficients[i];
    
    return {_col, _matrix(_row, _col)};
    */
    // Assuming operator++ skips to the next defined value
    return {_matrix._colIndices[_coeff_idx], _matrix._coefficients[_coeff_idx]};
  }

  std::pair<unsigned int, double&> operator->(){
    return *(*this);
  }
};

class CSRMatrixColRange {
  CSRMatrix& _matrix;
  unsigned int _row;
public:
  CSRMatrixColRange(CSRMatrix& m, unsigned int row)
    : _matrix(m)
    , _row(row)
  {}

  CSRMatrixColIterator begin(){
    return {_matrix, _matrix._rowStarts[_row]};
  }

  CSRMatrixColIterator end(){
    return {_matrix, _matrix._rowStarts[_row+1]};
  }
};

class CSRMatrixRowIterator {
  CSRMatrix& _matrix;
  unsigned int _row;
public:
  CSRMatrixRowIterator(CSRMatrix& m, unsigned int row)
    : _matrix(m)
    , _row(row)
  {}

  bool operator==(const CSRMatrixRowIterator& other) const{
    return _row==other._row;
  }

  bool operator!=(const CSRMatrixRowIterator& other) const{
    return !((*this)==other);
  }

  CSRMatrixRowIterator& operator++(){
    _row++;
    return *this;
  }

  std::pair<unsigned int, CSRMatrixColRange> operator*() const{
    return {_row, CSRMatrixColRange(_matrix, _row)};
  }

  std::pair<unsigned int, CSRMatrixColRange> operator->() const{
    return *(*this);
  }
};

class CSRMatrixRowRange{
  CSRMatrix& _matrix;
public:
  CSRMatrixRowRange(CSRMatrix& m)
    : _matrix(m)
  {}

  CSRMatrixRowIterator begin(){
    return {_matrix, 0};
  }

  CSRMatrixRowIterator end(){
    return {_matrix, _matrix.rows()};
  }
};

/*
CSRMatrixRowRange rows(CSRMatrix& m){
  return m;
}
*/

MatrixRowRange rows(Matrix& m){
  return m;
}

CSRMatrixRowRange rows(CSRMatrix& m){
  return m;
}


#endif