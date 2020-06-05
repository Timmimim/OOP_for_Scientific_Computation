#ifndef POLYNOMIAL_UTILS_H
#define POLYNOMIAL_UTILS_H

#include <array>

#include "polynomial.h"

namespace PU 
{
    namespace Interpolation
    {
        /**
        * Calculate Lagrange Basis for a set of Sample Points sp
        */
        template<size_t K>
        Polynomial<double,K> LagrangeBasis (std::array<double, K> sp) {
            // for all points in sp at respective index i
            //      build l_i by first creating a Polynom<2> 
            //      as x / x_i-x_j, -x_j / x_i - x_j for all x-es, 
            //      where x_i != x_j
            //      !: if x_i == x_j : Value of multiplier is 1, i.e. ommitted from calculation
            // Calculate P(x) as the sum of f_i * l_i 
            // using respective function values for x_i
            
            std::array<Polynomial<double,K>,sp.size()> l;
            for (size_t i = 0; i < sp.size(); ++i)
            {
                std::array<Polynomial<double, 2>, sp.size()-1> stepwise_polynomials;
                for (size_t j = 0, size_t pos = 0; j < sp.size(); ++j)
                {
                    if(j != i)
                    {
                        stepwise_polynomials[pos] = Polynomial({ -sp[j] / (sp[i]-sp[j]) , 1/sp[i]});
                        ++pos;
                    }
                }
                for (size_t j = 0; j < sp.size(); ++j)
                {
                    // auto product
                }
            }
        };

    }

    namespace Recursive
    {
        
    }
}


#endif