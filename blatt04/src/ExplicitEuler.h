#ifndef EXPLICIT_EULER_H
#define EXPLICIT_EULER_H

#include <vector>
#include <array>
#include <istream>

#include "../../blatt03/vector.h"
#include "ODESolver.h"
#include "ODE.h"

template <unsigned long N>
class ExplicitEuler 
        : public ODESolver<N> {

public:
    ExplicitEuler (ODE<N> &problem, const double start, const double step, const double end)
        : _problem(&problem), _initial_distribution(problem.getData()), _t(start), _dt(step), _T(end)  {};

    std::vector<std::array<double,N+1>> solve () {
        Vector x(N);
        for (size_t i = 0; i<N; ++i)
        {    
            x(i) = _initial_distribution[i];
        }

        double t = _t;

        std::vector<std::array<double,N+1>> data(N);
        data[0][0] = t;
        for (size_t i = 1; i <= N; ++i){
            data[0][i] = x(i-1);
        }

        while(t < _T)
        {
            auto dx = _problem->f(x);

            std::array<double,N+1> result;
            result[0] = t+1;

            for (size_t i = 0; i < N; ++i){
                x(i) += _dt * dx(i);
                result[i+1] = x(i);
            }
            data.push_back(result);
            t += _dt;
        }
        return data;
    };


private:

    ODE<N> *_problem;
    // std::function<std::array<double, N>(std::array<double,N>)> _problem;
    std::array<double,N> _initial_distribution;
    double _t;
    double _dt;
    double _T;
};

// template class ExplicitEuler<3ul>;

#endif