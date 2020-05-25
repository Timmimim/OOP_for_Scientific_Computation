#ifndef IMPLICIT_EULER_H
#define IMPLICIT_EULER_H

#include <functional>

#include "../../blatt03/matrix.h"
#include "../../blatt03/vector.h"
#include "matrix_util.h"
#include "ODESolver.h"

template <unsigned long N>
class ImplicitEuler 
        : public ODESolver<N> {
public:
    ImplicitEuler (ODE<N> &problem, const double start, const double step, const double end)
        : _problem(&problem), _initial_distribution(problem.getData()), _t(start), _dt(step), _T(end)  {};

    std::vector<std::array<double,N+1>> solve () {
        Vector x(N);
        for (size_t i = 0; i<N; ++i)
        {    
            x(i) = _initial_distribution[i];
        }

        // leave t intact to be reuseable later
        double t = _t;
        const int size = N+1;
        std::vector<std::array<double,size>> data(N);
        data[0][0] = t;
        for (size_t i = 1; i <= N; ++i){
            data[0][i] = x(i-1);
        }
        
        Vector fx = _problem->f(x);
        auto g_x = [](Vector x_init, Vector x_k, Vector fx, double dt) {return x_k - x_init + dt*fx;};

        while (t < _T)
        {
            Vector x_init ({0.,0.,0.});
            
            x = newton(g_x, x_init, x, fx, _dt);
            
            std::array<double,N+1> result;
            result[0] = t;

            for (size_t i = 0; i < N; ++i){
                result[i+1] = x(i);
            }

            data.push_back(result);
            
            t += _dt;
        }
        return data;
    }

    Vector newton(std::function<Vector(Vector, Vector, Vector, double)> g, Vector x_init, Vector x_k, Vector fx, double step)
    {
        const double tol = 1e-13;
        const int max_iter = 25;
        int iter = 0;
        Vector approx_x(x_init);
        Vector update_summand(N);
        /**
         * Calculate g(x^k)
         */
        //Vector fx = _problem->f(x_n);
        Vector gx = g(approx_x, x_k, fx, step);

        Matrix jacobi_g_inverse(N);
        Matrix const ID = MatUtil::id(N);

        while (iter <= max_iter)
        {
            // g' = J_g^-1 = (ID - dt*J_f)^-1
            MatUtil::invert(ID - _dt*_problem->JacobiMatrix_f(x_k), N, jacobi_g_inverse);
            
            // perform iteration step  x_n+1 = x_n - g(x)/g'(x) = x_n * J_g^-1 * g(x) 
            jacobi_g_inverse.mv(gx, update_summand);
            approx_x += update_summand;

            Vector fx = _problem->f(approx_x);
            gx = g(approx_x, x_k, fx, step);
            
            if(gx.normL1() < tol) break;
            iter++;
        }


        if(iter >= max_iter)
            throw std::runtime_error("Newton does not converge");

        return approx_x;

        //std::cout << "Values (x, x_k, f_i, dt)" << x << " " << x_i << " " << fx_i << " " << step << std::endl;
    };
    
private:
    ODE<N> *_problem;
    std::array<double,N> _initial_distribution;
    double _t;
    double _dt;
    double _T;
};

// template class ImplicitEuler<3ul>;

#endif