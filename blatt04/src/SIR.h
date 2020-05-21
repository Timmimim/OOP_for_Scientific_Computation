#ifndef SIR_H
#define SIR_H

#include <vector>;

#include "ODE.h"

class SIR : ODE {
public:
    /**
     * TODO: Implement me.
     */
private:
    double beta;
    double gamma;
    double S;
    double I;
    double R;
};

#endif