#ifndef POLYNOMIAL_UTILS_H
#define POLYNOMIAL_UTILS_H

#include <array>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

#include "polynomial.h"

namespace PU 
{

    namespace Recursive
    {
        template<typename T, int S, int N>
        static Polynomial<T,S> SetProductEqualDegree (std::array<Polynomial<T, N>, 1>& polynomials)
        {
            static_assert(N > 0, "Degree of Polynomial educts must be higher than 0");
            static_assert(S == N, "Anchor Polynomial must be returned, so degree must equal that of set of educts.");

            return polynomials[0];
        };

        template<typename T, int S, int N, size_t ARR_L >
        static Polynomial<T,S> SetProductEqualDegree (std::array<Polynomial<T, N>, ARR_L>& polynomials)
        {   
            static_assert(N > 0, "Degree of Polynomial educts must be higher than 0");
            static_assert(S >= N, "Resulting Polynomial must have equal or higher degree than educts.");

            Polynomial<T,N>& educt = polynomials[0];
            std::cout << educt << std::endl;

            std::array<Polynomial<double,2>,ARR_L-1> polynomials_subset;
                
            std::move(std::make_move_iterator(polynomials.begin() + 1), std::make_move_iterator(polynomials.end()), polynomials_subset.begin());
            return SetProductEqualDegree<double, S - (N-1), N> (polynomials_subset) *  educt;
        };
    }

    namespace Interpolation
    {
        /**
        * Calculate Lagrange Basis for a set of Sample Points sp
        */
        template<size_t K>
        static Polynomial<double,K> LagrangeBasis (std::array<double, K> sp_x, std::array<double, K> sp_fx) {
            // for all x_values in sp_x at respective index i
            //      build l_i by first creating a Polynom<2> 
            //      as x / x_i-x_j, -x_j / x_i - x_j for all x-es, 
            //      where x_i != x_j
            //      !: if x_i == x_j : Value of multiplier is 1, i.e. ommitted from calculation
            // Calculate P(x) as the sum of f_i * l_i 
            // using respective function values for x_i
            
            std::array<Polynomial<double,K>,sp_x.size()> l;
            
            std::array<Polynomial<double, 2>, K-1> stepwise_polynomials;
            for (size_t i = 0; i < K; ++i)
            {
                for (size_t j = 0, pos = 0; j < K; ++j)
                {
                    if(j != i)
                    {
                        Polynomial<double,2> step_polynomial ({ -sp_x[j] / (sp_x[i]-sp_x[j]) , 1/(sp_x[i]-sp_x[j])});
                        std::cout << step_polynomial << std::endl;
                        stepwise_polynomials[pos] = step_polynomial;
                        ++pos;
                    }
                };
                Polynomial<double, K> lagrange_polynomial = PU::Recursive::SetProductEqualDegree<double,K,2>(stepwise_polynomials);
                l[i] = lagrange_polynomial;
            }
            Polynomial<double,K> interpolation;
            for (size_t i = 0; i < sp_x.size(); ++i)
            {
                l[i] *= sp_fx[i]; 
                interpolation = interpolation + l[i];
            }
            return interpolation;
        };

    }
};


#endif