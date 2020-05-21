#ifndef SIR_H
#define SIR_H

#include <vector>

#include "ODE.h"

template <std::size_t N>
class SIR : 
        public ODE<N> {
public:
    SIR(double beta, double gamma, std::array<double,3> x)
        : _beta(beta), _gamma(gamma), _S(x[0]), _I(x[1]), _R(x[2]) {};

    virtual std::array<double,N> f() override{
        double infected = _beta * _S*_I / (_S+_I+_R);
        double recovered = _gamma * _I;
        _S -= infected;
        _I += infected-recovered;
        _R += recovered;
    };
    /*
    std::array<double,3> g()
    {

    };
    */

    std::array<double,3> currentPopulation()
    {
        return {_S,_I,_R};
    }

private:
    double _beta;
    double _gamma;
    double _S;
    double _I;
    double _R;
};

#endif