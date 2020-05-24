#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "ODE.h"

template <unsigned long N>
class ODESolver{
public:
    virtual ~ODESolver() {};
    virtual std::vector<std::array<double,N+1>> solve() = 0;
    
private:
    ODE<N> *_problem;
    // std::function<std::array<double, N>(std::array<double,N>)> _problem;
    std::array<double,N> _initial_distribution;
    double _t;
    double _dt;
    double _T;
};

// template class ODESolver<3ul>;

#endif