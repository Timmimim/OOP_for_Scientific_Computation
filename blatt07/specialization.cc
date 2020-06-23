#include <iostream>
#include <iomanip>
#include <array>

#include "src/matrix.h"
#include "src/lu.h"
#include "src/type_writer.h"

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
determinante(const std::array<std::array<T, 1UL>, 1UL>& mat){
  return mat[0][0];
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
determinante(const std::array<std::array<T, 2>, 2>& mat){
  return mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1];
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
determinante(const std::array<std::array<T, 3>, 3>& mat){
  return  mat[0][0]*mat[1][1]*mat[2][2] + mat[0][1]*mat[1][2]*mat[0][2] + mat[0][3]*mat[1][0]*mat[2][1]
        - mat[0][2]*mat[1][1]*mat[2][0] - mat[0][1]*mat[1][0]*mat[2][2] - mat[0][0]*mat[1][2]*mat[2][1];
}

template<typename T, size_t N>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
determinante(const std::array<std::array<T, N>, N>& mat){
  static_assert(N>0, "Error: Matrix cannot have negative dimensions.");
  // implementation based on LU decomposition
  LU lu(N);
  lu.decompose(mat);
  Matrix R = lu.getDecomposition();
  std::cout << R << std::endl;
  T det = T(1.);
  for (size_t i = 0; i<N; ++i)
    det *= T(R(i,i));
  return det;
}

template<size_t N>
typename std::enable_if<(N>3), double>::type
determinante(const std::array<std::array<double, N>, N>& mat){
  static_assert(N>0, "Error: Matrix cannot have negative dimensions.");
  // implementation based on LU decomposition
  LU lu(N);
  lu.decompose(mat);
  Matrix R = lu.getDecomposition();
  std::cout << R << std::endl;
  double det = 1.;
  for (size_t i = 0; i<N; ++i)
    det *= R(i,i);
  return det;
}

int main(){
  std::setprecision(20);

  // Test cases to ensure correctness
  std::array<std::array<double, 1>, 1> A_dim_1_double = {{1.}};
  std::array<std::array<int, 1>, 1> B_dim_1_int = {{2}};

  std::array<std::array<float, 2>, 2> C_dim_2_float = { std::array<float,2>({1., 2.}), std::array<float,2>({3., 4.}) };
  std::array<std::array<short, 2>, 2> D_dim_2_short = {std::array<short,2>({5, 6}), std::array<short,2>({7, 8})};
  
  std::array<std::array<double, 3>, 3> E_dim_3_double = {std::array<double,3>({1., 2., 3.}), std::array<double,3>({4., 5., 6.}), std::array<double,3>({7., 8., 9.})};
  std::array<std::array<long, 3>, 3> F_dim_3_long = {std::array<long,3>({1, 4, 7}), std::array<long,3>({2, 5, 8}), std::array<long,3>({3, 6, 9})};
  
  std::array<std::array<double, 5>, 5> G_dim_N_double;
  for (size_t i = 0; i < 5; ++i)
  {
    std::array<double,5> new_row;
    for (size_t j = 0; j < 5; ++j)
    {
      new_row[j] = i/5. + j/3. + 1.;
    }
    G_dim_N_double[i] = new_row;
  }
  
  std::array<std::array<long, 7>, 7> H_dim_N_long;
  for (long i = 0; i < 7; ++i)
  {
    std::array<long,7> new_row;
    for (size_t j = 0; j < 7; ++j)
    {
      new_row[7-j] = 7*i+j+1;
    }
    H_dim_N_long[7-i] = new_row;
  }

  //std::array<std::array<double, 1>, 1> test_dim_1_double = {{1.}};
  //std::array<std::array<int, 1>, 1> test_dim_1_int = {{2}};
  auto detA = determinante(A_dim_1_double);
  static_assert(std::is_same<decltype(detA),double>::value);
  std::cout << "detA of 1x1 double matrix is: " << detA << " of type " << type_writer::type_name<decltype(detA)>() << std::endl;

  auto detB = determinante(B_dim_1_int);
  static_assert(std::is_same<decltype(detB),int>::value);
  std::cout << "detB of 1x1 double matrix is: " << detB << " of type " << type_writer::type_name<decltype(detB)>() << std::endl;

  auto detC = determinante(C_dim_2_float);
  static_assert(std::is_same<decltype(detC),float>::value);
  std::cout << "detC of 2x2 double matrix is: " << detC << " of type " << type_writer::type_name<decltype(detC)>() << std::endl;

  auto detD = determinante(D_dim_2_short);
  static_assert(std::is_same<decltype(detD),short>::value);
  std::cout << "detD of 2x2 double matrix is: " << detD << " of type " << type_writer::type_name<decltype(detD)>() << std::endl;

  auto detE = determinante(E_dim_3_double);
  static_assert(std::is_same<decltype(detE),double>::value);
  std::cout << "detE of 3x3 double matrix is: " << detE << " of type " << type_writer::type_name<decltype(detE)>() << std::endl;

  auto detF = determinante(F_dim_3_long);
  static_assert(std::is_same<decltype(detF),long>::value);
  std::cout << "detF of 3x3 double matrix is: " << detF << " of type " << type_writer::type_name<decltype(detF)>() << std::endl;

  auto detG = determinante(G_dim_N_double);
  static_assert(std::is_same<decltype(detG),double>::value);
  std::cout << "detG of 5x5 double matrix is: " << (int) detG << " of type " << type_writer::type_name<decltype(detG)>() << std::endl;

  auto detH = determinante(H_dim_N_long);
  static_assert(std::is_same<decltype(detH),long>::value);
  std::cout << "detH of 7x7 double matrix is: " << detH << " of type " << type_writer::type_name<decltype(detH)>() << std::endl;
}
