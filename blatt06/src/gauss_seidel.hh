/**
 * Implements the iterative Gauss-Seidel solver for systems of linear equations
 * as a Templated class. 
 * This Gauss-Seidel solver can be applied to any matrix format that implements
 * Iterators and Ranges, which must supply a current index as well as values.
 */ 

#ifndef GAUSS_SEIDEL_HH
#define GAUSS_SEIDEL_HH

#include <iostream>

#include "../../blatt03/vector.h"
//#include "../../blatt03/matrix.h"
//#include "csrmatrix.hh"
#include "matrix_iterator.hh"
//#include "mv.hh"

template<class M>
class GaussSeidel
{
    const size_t _MAX_ITER;
    const double _TOL;
    size_t _iterations;

public: 
    GaussSeidel<M> (const size_t max_iter, const double tolerance_threshold)
    :   _MAX_ITER(max_iter)
    ,   _TOL(tolerance_threshold)
    ,   _iterations(0)
    {}

    void solve(const M& mat, const Vector& _b, Vector& x)
    {
        M _A = mat;
        double error = 1.;
        Vector x_temp (x);

        for (_iterations = 1; _iterations <= _MAX_ITER; ++_iterations)
        {
            error = 0.;
            for (auto [row_idx, cols] : rows(_A))
            {
                double step_sum_next = 0.;
                double step_sum_last = 0.;

                for (auto [col_idx, value] : cols)
                {
                    if (col_idx < row_idx)
                        step_sum_next += value * x_temp(col_idx);
                    else
                    if (col_idx > row_idx)
                        step_sum_last += value * x(col_idx);
                }
                double a_kk = _A(row_idx,row_idx);
                double b_k = _b(row_idx);
                x_temp(row_idx) = (b_k - step_sum_next - step_sum_last) / a_kk;
            }
            error = std::max(error, (x_temp - x).abs_val());
            x = x_temp;

            if (error < _TOL) break;
        }
    }

    size_t steps_until_convergence()
    {
        return _iterations;
    }
};

#endif