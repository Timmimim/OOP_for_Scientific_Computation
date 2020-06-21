#ifndef MV_HH
#define MV_HH

#include "../../blatt03/vector.h"
#include "matrix_iterator.hh"

template<class M>
Vector operator*(const M& mat, const Vector& v){
  M mat_copy(mat);
  Vector res(v.size());
  for (auto [row_idx, cols] : rows(mat_copy))
  {
    for (auto [col_idx, value] : cols)
    {
      std::cout << "Non-zero element of csr: " << row_idx << " x " << col_idx << " = " << value << std::endl;
      res(row_idx) += value * v(col_idx);
    }
  }
  std::cout << "Vector: [" << v << "]" << std::endl;
  return res;
}


#endif
