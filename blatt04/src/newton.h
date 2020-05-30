#ifndef NEWTON_H
#define NEWTON_H

#include <functional>

#include "matrix_util.h"
#include "../../blatt03/vector.h"
#include "../../blatt03/matrix.h"

namespace newton
{
    Vector multi_dimensional(   std::function<Vector(Vector, Vector, Vector, double)> g, 
                                std::function<Vector(Vector)> f,
                                std::function<Matrix(Vector)> jacobi, 
                                Vector x_0, 
                                Vector x_k, 
                                double step)
    {
        const double tol = 1e-13;
        const int max_iter = 25;
        int iter = 0;
        size_t _N = x_k.size();

        Vector approx_x(x_0);
        Vector update_summand(_N);
        
        Vector fx = f(x_k);
        Vector gx = g(approx_x, x_k, fx, step);

        Matrix jacobi_g_inverse(_N);
        Matrix const ID = MatUtil::id(_N);

        while (iter <= max_iter)
        {
            // g' = J_g^-1 = (ID - dt*J_f)^-1
            MatUtil::invert(ID - step*jacobi(x_k), _N, jacobi_g_inverse);
            
            // perform iteration step  x_n+1 = x_n - g(x)/g'(x) = x_n * J_g^-1 * g(x) 
            jacobi_g_inverse.mv(gx, update_summand);
            approx_x += update_summand;

            Vector fx = f(approx_x);
            gx = g(approx_x, x_k, fx, step);
            
            if(gx.normL1() < tol) break;
            iter++;
        }

        if(iter >= max_iter)
            throw std::runtime_error("Newton does not converge");

        return approx_x;
    };
}



#endif