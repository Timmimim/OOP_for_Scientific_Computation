#include <iostream>
#include <iomanip>
#include <ctime>

#include "../blatt03/vector.h"
#include "../blatt03/matrix.h"
#include "src/csrmatrix.hh"
#include "src/matrix_iterator.hh"
#include "src/gauss_seidel.hh"

int main()
{
    const size_t SIZE = 100;

    Matrix regular_matrix(SIZE,SIZE);
    for (int i = 0; i < SIZE; ++i)
    {
        regular_matrix(i,i) = 2.;
        if ((i-1) >= 0)
            regular_matrix(i, i-1) = -1.;
        if ((i+1) < SIZE)
            regular_matrix(i, i+1) = -1.;
    }

    CSRMatrix csr_matrix(SIZE,SIZE);
    for (int i = 0; i < SIZE; ++i)
    {
        if ((i-1) >= 0)
            csr_matrix.addCoefficient(i, i-1, -1.);
        csr_matrix.addCoefficient(i, i, 2.);
        if ((i+1) < SIZE)
            csr_matrix.addCoefficient(i, i+1, -1.);
    }

    Vector b (SIZE);
    for (int i = 0; i < SIZE; ++i)
        b(i) = 1.5 * i;

    Vector x_a (SIZE);
    for (int i = 0; i < SIZE; ++i)
        x_a(i) = 1.;


    Vector x_b (SIZE);
    for (int i = 0; i < SIZE; ++i)
        x_b(i) = 1.;

    const clock_t begin_time_regular_matrix = clock();
    GaussSeidel<Matrix> GS_regular (regular_matrix,b);
    GS_regular.solve(x_a);
    double runtime_gs_regular = double(clock() - begin_time_regular_matrix) / CLOCKS_PER_SEC;

    const clock_t begin_time_csr_matrix = clock();
    GaussSeidel<CSRMatrix> GS_csr (csr_matrix,b);
    GS_csr.solve(x_b);
    double runtime_gs_csr = double(clock() - begin_time_csr_matrix) / CLOCKS_PER_SEC;

    std::setprecision(20);
    std::cout << "Runtime GS using regular Matrix: " << runtime_gs_regular << std::endl;
    std::cout << "Runtime GS using CSR Matrix: " << runtime_gs_csr << std::endl;

    bool eq = true;
    for (int i = 0; i < SIZE; ++i)
        if (std::abs(x_a(i) - x_b(i)) > 1e-13)
            eq = false;
    
    if (eq)
        std::cout << "Results are equal." << std::endl;    
    
};
