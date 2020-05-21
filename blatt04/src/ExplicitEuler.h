#ifndef EXPLICIT_EULER_H
#define EXPLICIT_EULER_H

#include <functional>
#include <vector>
#include <array>

#include "ODESolver.h"

template <std::size_t N>
class ExplicitEuler : ODESolver {

public:

    std::vector<std::array<double,N+1>> solve {
        std::array<double,3> x = _initial_distribution;
        std::vector<std::array<double,4>> data( { {t, x[0], x[1], x[2]} } );
        double t = _t;
        while(t < _T)
        {
            auto dx = _problem(x);
            x[0] = x[0] + _dt * dx[0]; 
            x[1] += _dt * dx[1]; 
            x[2] += _dt * dx[2];
            data.push_back({t, x[0], x[1], x[2]});
            t += _dt;
        }
        return data;
    };


private:
    std::function<std::array<double, N>(std::array<double,N>)> _problem;
    std::array<double,3> _initial_distribution;
    double _t;
    double _dt;
    double _T;
};

#endif