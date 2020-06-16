#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "ODE.h"

template <unsigned long N>
class ODESolver{
public:
    virtual ~ODESolver() {};
    virtual std::vector<std::array<double,N+1>> solve() = 0;
};

#endif