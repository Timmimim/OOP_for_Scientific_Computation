#ifndef SIR_H
#define SIR_H

#include <vector>

#include "../../blatt03/matrix.h"
#include "../../blatt03/vector.h"
#include "ODE.h"

template <unsigned long N>
class SIR : 
        public ODE<N> {
public:
    SIR(double beta, double gamma, std::array<double,3> x)
        : _beta(beta), _gamma(gamma), _S(x[0]), _I(x[1]), _R(x[2]) {};

    Vector f(Vector data) final {
        double S = data(0);
        double I = data(1);
        double R = data(2);
        double N_ = S+I+R;
        double infected = _beta * S*I / (N_);
        double recovered = _gamma * I;
        Vector res({-infected, infected-recovered, recovered});
        return res;
    };

/*
    Matrix JacobiMatrix_f (std::array<double,N> data) override
    {
        auto [S,I,R] = data;
        double N_ = S+I+R;
        std::vector<double> row1 ({(-(_beta * I / N_)),  (-(_beta + S / N_)),          0.});
        std::vector<double> row2 ({_beta * I / N_,       (_beta * S / N_)-_gamma,       0.});
        std::vector<double> row3 ({0.,                  _gamma,                        0.});
        std::vector<std::vector<double>> matrix ({row1, row2, row3});
        return matrix;
    }
  */  
 
    Matrix JacobiMatrix_f (Vector data) final
    {
        double S = data(0);
        double I = data(1);
        double R = data(2);
        double N_ = S+I+R;
        std::vector<double> row1 ({(-(_beta * I / N_)),  (-(_beta + S / N_)),          0.});
        std::vector<double> row2 ({_beta * I / N_,       (_beta * S / N_)-_gamma,       0.});
        std::vector<double> row3 ({0.,                  _gamma,                        0.});
        std::vector<std::vector<double>> matrix ({row1, row2, row3});
        return matrix;
    }

    std::array<double,N> getData() const final
    {
        return {_S,_I,_R};
    }

    std::vector<double> getParameters() const
    {
        return {_beta, _gamma};
    }

private:
    double _beta;
    double _gamma;
    double _S;
    double _I;
    double _R;
};

#endif