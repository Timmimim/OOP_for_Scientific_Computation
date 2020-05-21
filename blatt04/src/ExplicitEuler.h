#ifndef EXPLICIT_EULER_H
#define EXPLICIT_EULER_H

#include <functional>
#include <vector>
#include <array>

#include "ODESolver.h"

template <std::size_t N>
class ExplicitEuler 
        : public ODESolver<N> {

public:

    std::vector<std::array<double,N+1>> solve () {
        std::array<double,N> x = _initial_distribution;

        double t = _t;

        std::vector<std::array<double,N+1>> data();
        data[0][0] = t;
        for (size_t i = 1; i <= N; ++i){
            data[0][i] = x[i-1];
        }

        while(t < _T)
        {
            auto dx = _problem(x);
            std::array<double,N+1> result;
            result[0] = t;
            
            x[0] = x[0] + _dt * dx[0];
            result[1] = x[0];

            for (size_t i = 1; i < N; ++i){
                x[i] += _dt * dx[i];
                result[i+1] = x[i];
            }
            data.push_back(result);
            t += _dt;
        }
        return data;
    };


private:
    std::function<std::array<double, N>(std::array<double,N>)> _problem;
    std::array<double,N> _initial_distribution;
    double _t;
    double _dt;
    double _T;
};

#endif