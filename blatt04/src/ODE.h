#ifndef ODE_H
#define ODE_H

#include <array>

#include "../../blatt03/vector.h"
#include "../../blatt03/matrix.h"

template <unsigned long N>
class ODE {
public:
    virtual ~ODE() {};

    virtual Vector f(Vector data_SIR) = 0;

    // virtual Matrix JacobiMatrix_f (std::array<double,N> data) = 0;
    
    virtual Matrix JacobiMatrix_f (Vector data) = 0;

    virtual std::array<double,N> getData() const = 0;

    // virtual std::vector<double> getParameters() = 0;

private:

};

#endif