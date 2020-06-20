#ifndef CSRMATRIX_H
#define CSRMATRIX_H

#include <vector>
#include <cassert>
#include "../blatt03/vector.h"

class CSRMatrix{
  std::vector<double> _coefficients;
  std::vector<unsigned int> _colIndices;
  std::vector<unsigned int> _rowStarts;
  unsigned int _rows, _cols;

  friend class CSRMatrixColIterator;
  friend class CSRMatrixColRange;

public:
  CSRMatrix(unsigned int rows, unsigned cols)
    : _rows(rows)
    , _cols(cols)
  {
    _rowStarts.push_back(0); // first row starts at 0
    _rowStarts.push_back(0); // first row is empty
  }

  CSRMatrix(const CSRMatrix& other)
    : _rows(other._rows)
    , _cols(other._cols)
    , _coefficients(other._coefficients)
    , _colIndices(other._colIndices)
    , _rowStarts(other._rowStarts)  
    {};

  // Coefficients must be added in row major order
  void addCoefficient(unsigned int row, unsigned int col, double x){
    assert(row > _rowStarts.size()-2 || (row==_rowStarts.size()-2 && (_colIndices.empty() || col > _colIndices.back()))); // coefficients must be added in row-wise order!
    for(unsigned r=_rowStarts.size()-1; r<=row; ++r){
      _rowStarts.push_back(_coefficients.size());
    }
    _rowStarts.back()++;
    _colIndices.push_back(col);
    _coefficients.push_back(x);
  }

  // The operator() is inefficient! Don't use it in the iterators!
  const double& operator()(unsigned int i, unsigned int j) const{
    auto start = _colIndices.begin()+_rowStarts[i];
    auto end = _colIndices.begin()+_rowStarts[i+1];
    auto it = std::lower_bound(start, end, j); // uses that the columns are sorted
    if(it != end && *it == j)
      return _coefficients[it - _colIndices.begin()];
    assert(false); // Index not in Matrix
  }

  double& operator()(unsigned int i, unsigned int j){
    auto start = _colIndices.begin()+_rowStarts[i];
    auto end = _colIndices.begin()+_rowStarts[i+1];
    auto it = std::lower_bound(start, end, j); // uses that the columns are sorted
    if(it != end && *it == j)
      return _coefficients[it - _colIndices.begin()];
    assert(false); // Index not in Matrix
  }

  unsigned int rows() const{
    return _rows;
  }

  unsigned int cols() const{
    return _cols;
  }
};

#endif
