#ifndef IMPLICIT_EULER_H
#define IMPLICIT_EULER_H

#include <functional>

#include "../../blatt03/matrix.h"
#include "../../blatt03/vector.h"
#include "newton.h"
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
        
        auto f = [this](Vector x) { return _problem->f(x);};
        auto g_x = [this](Vector x_0, Vector x_k, Vector f_x, double dt) {return x_k - x_0 + dt*f_x;};
        auto jac = [this](Vector x){return _problem->JacobiMatrix_f(x);};

        while (t < _T)
        {
            Vector x_init ({0.,0.,0.});
            
            x = newton::multi_dimensional(g_x, f, jac, x_init, x, _dt);

            std::array<double,N+1> result;
            result[0] = t+1;

            for (size_t i = 0; i < N; ++i){
                result[i+1] = x(i);
            }

            data.push_back(result);
            
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

#endif