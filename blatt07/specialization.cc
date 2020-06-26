#include <iostream>
#include <iomanip>
#include <array>

#include "src/matrix.h"
#include "src/lup.h"
#include "src/type_writer.h"

template <typename T, size_t M, size_t N>
std::ostream& operator <<(std::ostream& str, const std::array<std::array<T,N>,M>& m){
  if(M == 0 || N == 0){
    str << "Matrix of size 0";
    return str;
  }
  str << "[";
  for(size_t i = 0; i < M-1; ++i)
  {
    str << "\t[" << m[i][0];
    for(size_t j=1; j < N; ++j){
      str << ", " << m[i][j];
    }
    str << "]\n";
  }
  str << "\t[" << m[M-1][0];
  for(size_t j=1; j < N; ++j){
    str << ", " << m[M-1][0];
  }
  str << "]";
  str << " ]";
  return str;
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
determinant(const std::array<std::array<T, 1UL>, 1UL>& mat){
  return mat[0][0];
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
determinant(const std::array<std::array<T, 2>, 2>& mat){
  return mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1];
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
determinant(const std::array<std::array<T, 3>, 3>& mat){
  return  mat[0][0]*mat[1][1]*mat[2][2] + mat[0][1]*mat[1][2]*mat[0][2] + mat[0][3]*mat[1][0]*mat[2][1]
        - mat[0][2]*mat[1][1]*mat[2][0] - mat[0][1]*mat[1][0]*mat[2][2] - mat[0][0]*mat[1][2]*mat[2][1];
}

template<typename T, size_t N>
typename std::enable_if<std::is_arithmetic<T>::value, double>::type
determinant(const std::array<std::array<T, N>, N>& mat){
  static_assert(N>0, "Error: Matrix cannot have negative dimensions.");
  // implementation based on LU decomposition
  LUP lup(N);
  lup.LUPDecompose(mat);
  Matrix R = lup.getDecomposition();
  double det = 1.;
  for (size_t i = 0; i<N; ++i)
    det *= R(i,i);
  return lup.determinant_sign() * det;
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
  std::array<double,5> row1 = {21, -1, 19, -18, 17};
  std::array<double,5> row2 = {24,  3, 22, -21, 20};
  std::array<double,5> row3 = {27, -26, 100, -24, 23};
  std::array<double,5> row4 = {30, -29, 28, 1, 26};
  std::array<double,5> row5 = {33, -32, 31, 13,-99};
  G_dim_N_double = {row1, row2, row3, row4, row5};  
  
  std::array<std::array<long, 7>, 7> H_dim_N_long;
  for (long i = 0; i < 7; ++i)
  {
    std::array<long,7> new_row;
    for (size_t j = 0; j < 7; ++j)
    {
      new_row[6-j] = (7*i+j+1) * std::pow(-1,i);
    }
    H_dim_N_long[6-i] = new_row;
  }

  std::array<std::array<int, 5>, 5> I_dim_N_int;
  for (size_t i = 0; i < 5; ++i)
  {
    std::array<int,5> new_row;
    for (size_t j = 0; j < 5; ++j)
    {
      new_row[4-j] = (i*3 + j + 10) * std::pow(-1,j);
    }
    I_dim_N_int[i] = new_row;
  }

  auto detA = determinant(A_dim_1_double);
  static_assert(std::is_same<decltype(detA),double>::value);
  std::cout << "Matrix A:\n" << A_dim_1_double << std::endl;
  std::cout << "detA of 1x1 double matrix A is: " << detA << " of type " << type_writer::type_name<decltype(detA)>() << std::endl << std::endl;

  auto detB = determinant(B_dim_1_int);
  static_assert(std::is_same<decltype(detB),int>::value);
  std::cout << "Matrix B:\n" << B_dim_1_int << std::endl;
  std::cout << "detB of 1x1 int matrix is: " << detB << " of type " << type_writer::type_name<decltype(detB)>() << std::endl << std::endl;

  auto detC = determinant(C_dim_2_float);
  static_assert(std::is_same<decltype(detC),float>::value);
  std::cout << "Matrix C:\n" << C_dim_2_float << std::endl;
  std::cout << "detC of 2x2 float matrix is: " << detC << " of type " << type_writer::type_name<decltype(detC)>() << std::endl << std::endl;

  auto detD = determinant(D_dim_2_short);
  static_assert(std::is_same<decltype(detD),short>::value);
  std::cout << "Matrix D:\n" << D_dim_2_short << std::endl;
  std::cout << "detD of 2x2 short matrix is: " << detD << " of type " << type_writer::type_name<decltype(detD)>() << std::endl << std::endl;

  auto detE = determinant(E_dim_3_double);
  static_assert(std::is_same<decltype(detE),double>::value);
  std::cout << "Matrix E:\n" << E_dim_3_double << std::endl;
  std::cout << "detE of 3x3 double matrix is: " << detE << " of type " << type_writer::type_name<decltype(detE)>() << std::endl << std::endl;

  auto detF = determinant(F_dim_3_long);
  static_assert(std::is_same<decltype(detF),long>::value);
  std::cout << "Matrix F:\n" << F_dim_3_long << std::endl;
  std::cout << "detF of 3x3 long matrix is: " << detF << " of type " << type_writer::type_name<decltype(detF)>() << std::endl << std::endl;

  auto detG = determinant(G_dim_N_double);
  static_assert(std::is_same<decltype(detG),double>::value);
  std::cout << "Matrix G:\n" << G_dim_N_double << std::endl;
  std::cout << "detG of 5x5 double matrix is: " << (int) detG << " of type " << type_writer::type_name<decltype(detG)>() << std::endl << std::endl;

  auto detH = determinant(H_dim_N_long);
  static_assert(std::is_same<decltype(detH),double>::value);
  std::cout << "Matrix H:\n" << H_dim_N_long << std::endl;
  std::cout << "detH of 7x7 long matrix is: " << detH << " of type " << type_writer::type_name<decltype(detH)>() << std::endl << std::endl;

  auto detI = determinant(I_dim_N_int);
  static_assert(std::is_same<decltype(detI),double>::value);
  std::cout << "Matrix I:\n" << I_dim_N_int << std::endl;
  std::cout << "detI of 5x5 int matrix is: " << detI << " of type " << type_writer::type_name<decltype(detI)>() << std::endl << std::endl;  
}
