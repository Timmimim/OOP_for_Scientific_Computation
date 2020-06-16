#ifndef MATRIX_UTIL_J
#define MATRIX_UTIL_J

#include "../../blatt03/matrix.h"

namespace MatUtil {
    
  // calculate the cofactor of element (row,col)
  int getMinor(const Matrix& source, Matrix& target, const int row, const int col, const int order)
  {
      // indicate which col and row is being copied to target
      int colCount=0,rowCount=0;
  
      for(int i = 0; i < order; i++ )
      {
          if( i != row )
          {
              colCount = 0;
              for(int j = 0; j < order; j++ )
              {
                  // when j is not the element; otherwise skip
                  if( j != col )
                  {
                      target(rowCount,colCount) = source(i,j);
                      colCount++;
                  }
              }
              rowCount++;
          }
      }
  
      return 1;
  }
  
  // Calculate the determinant recursively
  double calculateDeterminant(const Matrix& mat, const unsigned int order)
  {
      // order must be > 0
      assert(order > 0);

      // stop the recursion when matrix is a single element
      if( order == 1 )
          return mat(0,0);
  
      double determinant = 0;
  
      // cofactor matrix
      Matrix minor = Matrix(order-1);
      
      for(int i = 0; i < order; i++ )
      {
          // get minor of element (0,i)
          getMinor( mat, minor, 0, i , order);
  
          // recursively calculate determinant
          determinant += (i%2==1?-1.0:1.0) * mat(0,i) * calculateDeterminant(minor,order-1);
          //det += pow( -1.0, i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
      }

      return determinant;
  }

  /**
   * Matrix Inversion
   * Implementation closely following https://chi3x10.wordpress.com/2008/05/28/calculate-matrix-inversion-in-c/
   * 
   * The result is written directly into target matrix Y
   */
  void invert(const Matrix& A, const unsigned int order, Matrix& Y)
  {
      // get the determinant of a
      double det = 1.0/calculateDeterminant(A,order);
  
      Matrix minor = Matrix(order-1);
  
      for(int j=0;j<order;j++)
      {
          for(int i=0;i<order;i++)
          {
              // get the co-factor (matrix) of A(j,i)
              getMinor(A, minor, j, i, order);
              Y(i,j) = det * calculateDeterminant(minor,order-1);
              if( (i+j)%2 == 1)
                  Y(i,j) = -Y(i,j);
          }
      }
  }

  Matrix id(unsigned int dim)
  {
    Matrix id(dim);
    for (size_t i = 0; i < dim; ++i)
      id(i,i) = 1;
    return id;
  }
}

#endif