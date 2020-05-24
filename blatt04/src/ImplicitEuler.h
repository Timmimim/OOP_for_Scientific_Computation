#ifndef IMPLICIT_EULER_H
#define IMPLICIT_EULER_H

#include <functional>

#include "../../blatt02/autodiff/ad.hh"
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

        Matrix jacobi_g_inverse(N);
        Matrix const ID = MatUtil::id(N);

        /**
         * Calculate g(x^k) using the Ad::SimpleAd class
         * Current implementation of Ad only works for a double param at a time
         * --> run stepwise per scalar, which is possible since g(x) uses addition only
         */
        Vector g(N);      // resulting vector g(x)
        auto f_x = _problem->f();  // full vector f(x)
        // use only f_x[i]
        auto g_x = [](Ad::SimpleAd x, double x_k, double f_i, double dt) {return x_k - x + dt*f_i;};
        
        while (t < _T)
        {
            // calculate each scalar to g(x)
            for (size_t i = 0; i<N; ++i)
                g(i) = newton(g_x, Ad::SimpleAd(x(i)), x(i), f_x[i], _dt);

            // g' = J_g^-1 = (ID - dt*J_f)^-1
            MatUtil::invert(ID - _dt*_problem->JacobiMatrix_f(), N, jacobi_g_inverse);
            
            // perform iteration step  x_n+1 = x_n - g(x)/g'(x) = x_n * J_g^-1 * g(x) 
            Vector implicit_update(N);
            jacobi_g_inverse.mv(g, implicit_update);
            x -= implicit_update;

            std::array<double,N+1> result;
            result[0] = t;

            for (size_t i = 0; i < N; ++i){
                result[i+1] = x(i);
            }
            data.push_back(result);
            _problem->updateData(f_x);
            t += _dt;
        }
        return data;
    }
private:
    ODE<N> *_problem;
    std::array<double,N> _initial_distribution;
    double _t;
    double _dt;
    double _T;
};

double newton(std::function<Ad::SimpleAd(Ad::SimpleAd, double, double, double)> f, Ad::SimpleAd start, double x_i, double fx_i, double step)
    {
        const double tol = 1e-13;
        const int max_iter = 20;
        int iter = 0;
        double x(start);
        Ad::SimpleAd fx = f(Ad::SimpleAd(x), x_i, fx_i, step);
        // f is defined by:
        //                      x_k - x + dt*f_i

        std::cout << "Values (x, x_k, f_i, dt)" << x << " " << x_i << " " << fx_i << " " << step << std::endl;

        std::cout << "Explicit Solver running into newton" << std::endl;
        for(; iter < max_iter;++iter){
            x = x - fx.value() / fx.derivative();
            fx = f(Ad::SimpleAd(x), x_i, fx_i, step);

            std::cout << "x: " << x << ", fx: " << fx.value() << " " << fx.derivative() << std::endl;
            if(std::abs(fx.value()) < tol) break;
        }
        if(iter >= max_iter)
            throw std::runtime_error("Newton does not converge");
        return x;
    };

// template class ImplicitEuler<3ul>;

#endif