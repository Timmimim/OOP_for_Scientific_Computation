#include <iostream>

#include "src/polynomial.h"
#include "src/polynomial_utils.h"


int main()
{
    std::array<int,3> data_A {{1,2,3}};
    std::array<int,4> data_B {{4,3,2,1}};
    std::array<double,3> data_X {{1.,2.5,3.}};
    std::array<double,3> data_Z {{1.5,3.,2.}};
    std::array<double,4> data_Y {{4.,3.5,2.,5.7}};

    Polynomial<int,3> A(data_A);
    Polynomial<int,4> B(data_B);
    Polynomial<double,3> X(data_X);
    Polynomial<double,3> Z(data_Z);
    Polynomial<double,4> Y(data_Y);

    auto C = A + B;
    std::cout << C << std::endl;

    auto D = A - B;
    std::cout << D << std::endl;
    
    auto E = X + Y;
    std::cout << E << std::endl;
    
    auto F = X - Y;
    std::cout << F << std::endl;

    auto G = Y - X;
    std::cout << G << std::endl;

    auto H = X - Z;
    std::cout << H << std::endl;

    auto I = X * Z;
    std::cout << I << std::endl;
    
    auto J = X * B;
    std::cout << J << std::endl;

    auto K = differentiate(A);
    std::cout << K << std::endl;

    auto L = differentiate(Y);  
    std::cout << L << std::endl;

    auto M = differentiate(differentiate(differentiate(Y)));  
    std::cout << M << std::endl;
}