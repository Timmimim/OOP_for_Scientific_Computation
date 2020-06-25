#ifndef LU_H
#define LU_H

#include "vector.h"
#include "matrix.h"
#include <assert.h>
#include <iostream>

class LU{
  // decomposition is done in-place, so this matrix contains both L and R;
  // lower-left half BELOW diagonal contains L (minus the diagonal being strictly 1s)
  // upper-right half INCLUDING diagonal is R.
  // decouple the two matrices and multiply them to receice A.
  Matrix _decomposition; // store the decomposition in this matrix

  // can easily be decoupled to work not-in-place, by writing partial result into auxiliary matrices
  // Matrix _L;
  // Matrix _R;

public:
  LU(unsigned int size=0) : _decomposition(size){};

  Matrix getDecomposition()
  {
    return _decomposition;
  }

  // decomposing the Matrix m, without modifing it
  void decompose(const Matrix& m){
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
        assert(m(i,i) != 0.);
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
  void decompose(Matrix&& m){
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
   * Ax = b,  A = LR   with P being a permutation matrix
   * <=>  LRb = b
   * 
   * def auxiliary variable y := Rx  => Ly = b,  Rx = y
   * 
   * use forward insertion (is that how you would translate Vorwärts-Einsetzen?) to calculate y, 
   * then use backward insertion to calculate x (which is the target).
   */
  void solve(const Vector& b, Vector& x){
    size_t dim = _decomposition.rows();
    Matrix L(dim);
    Matrix R(dim);
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
};

#endif
