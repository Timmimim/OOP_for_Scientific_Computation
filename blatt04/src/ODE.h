#ifndef ODE_H
#define ODE_H

#include <array>

#include "../../blatt03/vector.h"
#include "../../blatt03/matrix.h"

template <unsigned long N>
class ODE {
public:
    virtual ~ODE() {};

    virtual std::array<double,N> f() = 0;

    virtual Vector f(Vector data_SIR) = 0;

    virtual Matrix JacobiMatrix_f() = 0;

    virtual Matrix JacobiMatrix_f (std::array<double,N> data) = 0;
    
    virtual Matrix JacobiMatrix_f (Vector data) = 0;

    virtual std::array<double,N> getData() = 0;

    virtual std::vector<double> getParameters() = 0;

    virtual void updateData(std::array<double,N> update_summands) = 0;

private:

};

//template class ODE<3ul>;

#endif