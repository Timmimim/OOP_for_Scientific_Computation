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
    std::setprecision(20);
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

    std::cout << "Runtime GS using regular Matrix: " << runtime_gs_regular << std::endl;
    std::cout << "Runtime GS using CSR Matrix: " << runtime_gs_csr << std::endl;

    bool eq = true;
    for (int i = 0; i < SIZE; ++i)
        if (std::abs(x_a(i) - x_b(i)) > 1e-13)
            eq = false;
    
    if (eq)
    {
        std::cout << "Results are equal, ";
        int steps_regular = GS_regular.steps_until_convergence();
        int steps_csr = GS_csr.steps_until_convergence();
        if (steps_regular == steps_csr)
        {
            std::cout << "and were achieved in an equal number of iterations (" << steps_csr << ")." << std::endl;
            std::cout << "Using a CSR matrix improved performance significantly, to " << steps_csr / runtime_gs_csr << " calculation steps per second, from " << steps_regular / runtime_gs_regular << " using a conventional matrix format." << std::endl;
            std::cout << "As each iteration step's results are equal, this constitutes an increase in speed for the solver by the factor " << runtime_gs_regular/runtime_gs_csr << "." << std::endl;
            std::cout << "This is due, however not directly proportional to the skipped zero-multiplications (only ~3 in 100 values are non-zero)." << std::endl; 
            std::cout << "The non-proportional speed-up, in turn, is due to the fact that both matrix formats are being iterated over using Ranges and Iterators, with constructor calls making up part of the workload." << std::endl;
        }
        else if ( std::abs(steps_regular - steps_csr) <= 5)
            std::cout << "and were achieved in roughly the same number of iterations (" << steps_regular << " vs " << steps_csr << ")." << std::endl;
        else
            std::cout << "but number of iterations required was notably different (" << steps_regular << " vs " << steps_csr << ")." << std::endl;
    }
};
