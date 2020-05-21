#ifndef EXPLICIT_EULER_H
#define EXPLICIT_EULER_H

#include <functional>

#include "ODESolver.h";

class ExplicitEuler : ODESolver {
public:
    std::vector<std::array<double,4>> solve;
private:
    std::function<std::array<double,3>(std::array<double,3>)> func;
    std::array<double,3> x0;
    double t;
    double dt;
    double T;
};

#endif