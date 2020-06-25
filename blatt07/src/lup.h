#ifndef LUP_H
#define LUP_H

#include <cassert>
#include <iostream>
#include <array>

#include "vector.h"
#include "matrix.h"

class LUP{
  // decomposition is done in-place, so this matrix contains both L and R;
  // lower-left half BELOW diagonal contains L (minus the diagonal being strictly 1s)
  // upper-right half INCLUDING diagonal is R.
  // decouple the two matrices and multiply them to receice A.
  Matrix _decomposition; // store the decomposition in this matrix
  Vector _P; // pivoting -> stores column indices where permutation matrix has "1"s (i.e. swapped rows)

  // can easily be decoupled to work not-in-place, by writing partial result into auxiliary matrices
  // Matrix _L;
  // Matrix _R;

public:
  LUP(unsigned int size=0) : _decomposition(size,size), _P(size+1) {};

  Matrix getDecomposition()
  {
    return _decomposition;
  }

  // decomposing the Matrix m, without modifing it
  void decompose_unpivoted(const Matrix& m){
    assert(m.cols() == m.rows());

    size_t dim = m.cols();
    // allocate memory for decomposition
    _decomposition = m;

    for (size_t i = 0; i < dim-1; ++i)
    {
      // iterate over "remaining" matrix rows beyond current index
      for (size_t k = i+1; k < dim; ++k)
      {
        // calculate L, first assure m(i,i) != 0.
        assert(_decomposition(i,i) != 0.);
        _decomposition(k,i) = _decomposition(k,i) / _decomposition(i,i);

        // iterate over "remaining" matrix cols beyond current index
        for (size_t j = i+1; j < dim; ++j)
        {
          // calculate R
          _decomposition(k,j) = _decomposition(k,j) - _decomposition(k,i)*_decomposition(i,j);
        }
      }
    }
  }

  // templated decomposition of Matrix provided as std::array of std::arrays m, without modifing it
  template <typename T, size_t N>
  void decompose_unpivoted(const std::array<std::array<T,N>,N> & in_mat){
    Matrix m (N,N);
    for (size_t i = 0; i<N; ++i)
    {
      for (size_t j = 0; j<N; ++j)
      {
        m(i,j) = in_mat[i][j];
      }
    }

    size_t dim = N;
    // allocate memory for decomposition
    _decomposition = m;

    for (size_t i = 0; i < dim-1; ++i)
    {
      // iterate over "remaining" matrix rows beyond current index
      for (size_t k = i+1; k < dim; ++k)
      {
        // calculate L, first assure m(i,i) != 0.
        assert(_decomposition(i,i) != 0.);
        _decomposition(k,i) = _decomposition(k,i) / _decomposition(i,i);

        // iterate over "remaining" matrix cols beyond current index
        for (size_t j = i+1; j < dim; ++j)
        {
          // calculate R
          _decomposition(k,j) = _decomposition(k,j) - _decomposition(k,i)*_decomposition(i,j);
        }
      }
    }
  }

  // decompose the Matrix m, reuse its resources
  void decompose_unpivoted(Matrix&& m){
    assert(m.cols() == m.rows());

    for (size_t i = 0; i < m.rows()-1; ++i)
    {
      // iterate over "remaining" matrix rows beyond current index
      for (size_t k = i+1; k < m.rows(); ++k)
      {
        // calculate L, first assure m(i,i) != 0.
        assert(m(i,i) != 0.);
        m(k,i) = m(k,i) / m(i,i);

        // iterate over "remaining" matrix cols beyond current index
        for (size_t j = i+1; j < m.cols(); ++j)
        {
          m(k,j) = m(k,j) - m(k,i)*m(i,j);
        }
      }
    }
    _decomposition = m;
  }

  /**
   * Ax = b,  PA = LR   with P being a permutation matrix, ommitted in this case
   * <=>  LRx = b
   * 
   * def auxiliary variable y := Rx  => Ly = b,  Rx = y
   * 
   * use forward insertion (is that how you would translate Vorwärts-Einsetzen?) to calculate y, 
   * then use backward insertion to calculate x (which is the target).
   */
  void solve_unpivoted(const Vector& b, Vector& x){
    size_t dim = _decomposition.rows();
    Matrix L(dim,dim);
    Matrix R(dim,dim);
    Vector y(dim);

    for (size_t i = 0; i < dim; ++i)
    {
      for (size_t j = i; j < dim; ++j)
      {
        if(i==j)
        {
          L(i,j) = 1.;
          R(i,j) = _decomposition(i,j);
        }
        else
        {
          L(j,i) = _decomposition(j,i);
          R(i,j) = _decomposition(i,j);
        }
      }
    }


    /**
     * some outputs for stepwise validation
     * 
     * wrapped into own scope to make them collapsible and also easily deactivatable
     */
    /*
    { // terminal output scope
      std::cout << "\nIn-place _decomposition:\n";
      for (size_t i = 0; i < _decomposition.rows(); ++i)
      {
        for (size_t j = 0; j < _decomposition.cols(); ++j)
        {
            std::cout << _decomposition(i,j) << "  ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";

      Matrix LR = L*R;
      std::cout << "\nL:\n";
      for (size_t i = 0; i < L.rows(); ++i)
      {
        for (size_t j = 0; j < L.cols(); ++j)
        {
            std::cout << L(i,j) << "  ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";

      std::cout << "\nR:\n";
      for (size_t i = 0; i < R.rows(); ++i)
      {
        for (size_t j = 0; j < R.cols(); ++j)
        {
            std::cout << R(i,j) << "  ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";

      std::cout << "\nLR (=A)(=m):\n";
      for (size_t i = 0; i < LR.rows(); ++i)
      {
        for (size_t j = 0; j < LR.cols(); ++j)
        {
            std::cout << LR(i,j) << "  ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
   
    } // end terminal outputs
    */

    // Calculate auxiliary vector y using L and b
    // 1/L(i,i) and other occurences of L(i,i) included for the sake of completeness;
    // Since the main diagonal of the matrix L consists of 1s by definition, it could well be omitted.
    for (size_t i = 0; i < L.rows(); ++i)
    {
      // y(i) = (1 / L(i,i)) * (b(i) - sum(L(i,k)*y(k)) with sum over k=1 to i-1
      double sum_of_products = 0.;
      for (size_t k = 0; k < i; ++k)
      {
        sum_of_products += L(i,k) * y(k);
      }
      y(i) = (1/L(i,i)) * (b(i) - sum_of_products);
    }


    /*
    { // validation output for auxiliary vector y, again wrapped in own scope
      std::cout << "\nMy result for y:\n";
      for (size_t r = 0; r < y.size(); ++r)
      {
          std::cout << y(r) << "\n";
      }
    }
    */

    // Use y and R to calculate x
    // Start from the back, i.e. x(n) is set first for a vector x of size n+1;
    // from there values are calculated backwards
    size_t n = x.size()-1;
    x(n) = y(n) / R(n,n);
    for (int i = n-1; i >= 0; --i)
    {
      // x(i) = (1 / R(i,i)) * (y(i) - sum(R(i,k) * x(k)) with sum over k=i+1 to n
      //double sum_of_products = 0.;
      x(i) = y(i);
      for (size_t k = i+1; k < n+1; ++k)
      {
        //sum_of_products += R(i,k) * x(k);
        x(i) -= R(i,k) * x(k);
      }
      //x(i) = (1/R(i,i)) * (y(i) - sum_of_products);
      x(i) = x(i) / R(i,i);
    }
  }

  /**
   * Implementation of pivoted LU Decomposition following online example written in C.
   * Translated to C++ with custom Matrix and Vector formats.
   */
  void LUPDecompose(const Matrix& A) 
  {
    assert(A.cols() == A.rows());
    int idx_max_val; 
    size_t dim = A.rows();
    double col_max, abs_col_max;

    _decomposition = A;

    for (size_t i = 0; i <= dim; i++)
      _P(i) = i; //Unit permutation matrix (value is row of 1's), P(N) (counting pivots) initialized with N
      // Usage in Solver: Iterate over matrix, but instead of using row index r directly, use value of _P(r) to get swapped row back in place

    for (size_t i = 0; i < dim-1; i++)
    {
      col_max = 0.0;
      idx_max_val = i;

      for (size_t k = i; k < dim; k++)
        if ((abs_col_max = std::abs(_decomposition(k,i))) > col_max) 
        { 
          col_max = abs_col_max;
          idx_max_val = k;
        }

      assert(col_max != 0.); //failure, matrix is degenerate, max absolute value is near 0

      if (idx_max_val != i) 
      {
        //pivoting P
        size_t temp = _P(i);
        _P(i) = _P(idx_max_val);
        _P(idx_max_val) = temp;

        //pivoting rows of A
        double swap_temp;
        for (size_t c = 0; c < dim; ++c)
        {
          swap_temp = _decomposition(i,c);
          _decomposition(i,c) = _decomposition(idx_max_val, c);
          _decomposition(idx_max_val,c) = swap_temp;
        }

        //counting pivots starting from N (for determinant)
        _P(dim)++;
      }

      // iterate over "remaining" matrix rows beyond current index
      for (size_t k = i+1; k < dim; ++k)
      {
        // calculate L, first assure m(i,i) != 0.
        assert(_decomposition(i,i) != 0.);
        _decomposition(k,i) = _decomposition(k,i) / _decomposition(i,i);

        // iterate over "remaining" matrix cols beyond current index
        for (size_t j = i+1; j < dim; ++j)
        {
          // calculate R
          _decomposition(k,j) = _decomposition(k,j) - _decomposition(k,i)*_decomposition(i,j);
        }
      }
    };  //decomposition done 
  }

  /**
   * Templated version of LUPDecompose to work with StdArray of StdArray implementation. 
   */
  template<typename T, size_t N>
  typename std::enable_if<std::is_arithmetic<T>::value, void>::type
  LUPDecompose(const std::array<std::array<T,N>,N>& A) 
  {
    int idx_max_val; 
    size_t dim = N;
    double col_max;
    Matrix m(N,N);
    for (size_t i = 0; i<N; ++i)
    {
      for (size_t j = 0; j<N; ++j)
      {
        m(i,j) = A[i][j];
      }
    }
    _decomposition = m;

    for (size_t i = 0; i <= dim; ++i)
      _P(i) = i; //Unit permutation matrix (index is column, value is row of 1's), P(N) (counting pivots) initialized with N

    for (size_t i = 0; i < dim-1; ++i)
    {
      col_max = 0.0;
      idx_max_val = i;
      for (size_t k = i; k < dim; ++k)
      {
        if (std::abs(_decomposition(k,i)) > col_max) 
        { 
          col_max = std::abs(_decomposition(k,i));
          idx_max_val = k;
        }
      }

      assert(col_max != 0.); //failure, matrix is degenerate, max absolute value is near 0

      if (idx_max_val != i) 
      {
        //pivoting P
        size_t temp = _P(i);
        _P(i) = _P(idx_max_val);
        _P(idx_max_val) = temp;

        //pivoting rows of A
        double swap_temp;
        for (size_t c = 0; c < dim; ++c)
        {
          swap_temp = _decomposition(i,c);
          _decomposition(i,c) = _decomposition(idx_max_val, c);
          _decomposition(idx_max_val,c) = swap_temp;
        }

        //counting pivots starting from N (for determinant)
        _P(dim)++;
      }

      // iterate over "remaining" matrix rows beyond current index
      for (size_t k = i+1; k < dim; ++k)
      {
        // calculate L, first assure m(i,i) != 0.
        assert(_decomposition(i,i) != 0.);
        _decomposition(k,i) = _decomposition(k,i) / _decomposition(i,i);

        // iterate over "remaining" matrix cols beyond current index
        for (size_t j = i+1; j < dim; ++j)
        {
          // calculate R
          _decomposition(k,j) = _decomposition(k,j) - _decomposition(k,i)*_decomposition(i,j);
        }
      }
    };  //decomposition done 
  }

  /**
   * Implementation of pivoted LU Solver following online example written in C.
   * Translated to C++ with custom Matrix and Vector formats.
   */
  void LUPSolve(const Vector& b, Vector& x) 
  {
    size_t dim = _decomposition.rows();
    for (size_t i = 0; i < dim; i++) 
    {
      x(i) = b(_P(i));

      for (int k = 0; k < i; k++)
        x(i) -= _decomposition(i,k) * x(k);
    }

    for (int i = dim - 1; i >= 0; i--) 
    {
      for (int k = i + 1; k < dim; k++)
        x(i) -= _decomposition(i,k) * x(k);

      x(i) /= _decomposition(i,i);
    }
  }

  /**
   * Implementation of pivoted LU Decomposition Inversion following online example written in C.
   * Translated for practice completion only, this is not used.
   */
  void LUPInvert(Matrix& IA) 
  {
    size_t dim = _decomposition.rows();
    for (int j = 0; j < dim; ++j) 
    {
      for (int i = 0; i < dim; ++i) 
      {
        if (_P(i) == j) 
          IA(i,j) = 1.0;
        else
          IA(i,j) = 0.0;

        for (int k = 0; k < i; ++k)
          IA(i,j) -= _decomposition(i,k) * IA(k,j);
      }

      for (int i = dim - 1; i >= 0; --i) 
      {
        for (int k = i + 1; k < dim; ++k)
          IA(i,j) -= _decomposition(i,k) * IA(k,j);

        IA(i,j) = IA(i,j) / _decomposition(i,i);
      }
    }
  }

  /**
   * Implementation of Determinant Calculation using LUP Decomposition results, following online example written in C.
   * Translated to C++ with custom Matrix and Vector formats.
   * Implemented for completeness' sake, as determinants are calculated in `specialization.cc` via specialized template functions.
   */
  double LUPDeterminant() 
  {
    size_t dim = _decomposition.rows();
    double det = _decomposition(0,0);
    if(det == 0.)
      return det;

    for (int i = 1; i < dim; ++i)
      det *= _decomposition(i,i);

    if ( (size_t(_P(dim)) - dim) % 2 == 0)
      return det; 
    else
      return -det;
  }

  int determinant_sign()
  {
    size_t dim = _decomposition.cols();
    if ( (size_t(_P(dim)) - dim) % 2 == 0)
      return 1;
    else 
      return -1;
  }
};

#endif