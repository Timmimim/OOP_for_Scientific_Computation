#ifndef SIR_H
#define SIR_H

#include <vector>

#include "../../blatt03/matrix.h"
#include "ODE.h"

template <unsigned long N>
class SIR : 
        public ODE<N> {
public:
    SIR(double beta, double gamma, std::array<double,3> x)
        : _beta(beta), _gamma(gamma), _S(x[0]), _I(x[1]), _R(x[2]) 
    {
        _N = _S + _I + _R;
    };

    std::array<double,N> f() override {
        double infected = _beta * _S*_I / (_N);
        double recovered = _gamma * _I;
        return {-infected, infected-recovered, recovered};
    };

    Matrix JacobiMatrix_f() override
    {   
        std::vector<double> row1 ({(-(_beta * _I / _N)),   (-(_beta + _S / _N)),          0.});
        std::vector<double> row2 ({_beta * _I / _N,       (_beta * _S / _N)-_gamma,       0.});
        std::vector<double> row3 ({0.,                     _gamma,                        0.});
        std::vector<std::vector<double>> matrix ({row1, row2, row3});
        return matrix;
    }

    std::array<double,N> getData() override
    {
        return {_S,_I,_R};
    }

    void updateData(std::array<double,3> update_summands) override
    {
        _S += update_summands[0];
        _I += update_summands[1];
        _R += update_summands[2];
    }

private:
    double _beta;
    double _gamma;
    double _S;
    double _I;
    double _R;
    double _N;
};

//template class SIR<3ul>;

#endif