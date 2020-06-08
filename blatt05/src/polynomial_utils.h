#ifndef POLYNOMIAL_UTILS_H
#define POLYNOMIAL_UTILS_H

#include <array>
#include <vector>
#include <cassert>

#include "polynomial.h"

namespace PU 
{

    namespace Recursive
    {
        template<typename T, size_t M, size_t N, size_t S>
        Polynomial<T, M + (N-1)*(S-1) > SetProductEqualDegree (Polynomial<T,M>& factor, std::vector<Polynomial<T, N>>& polynomials)
        {   
            assert(!polynomials.empty());

            auto next = polynomials.back();
            polynomials.pop_back();
            if (polynomials.empty())
            {
                return factor * next;
            }
            else 
            {
                return factor * SetProductEqualDegree<S-1>(next, polynomials);
            }
        };


        template<typename T, size_t N>
        auto SetProductEqualDegree (std::vector<Polynomial<T, N>>& polynomials)
        {   
            assert(!polynomials.empty());

            Polynomial<T,N> next = polynomials.back();
            polynomials.pop_back();
            if (polynomials.empty())
            {
                return next;
            }
            else 
            {
                auto res = SetProductEqualDegree<polynomials.size()> (next, polynomials);
                return res;
            }
        };
    }

    namespace Interpolation
    {
        /**
        * Calculate Lagrange Basis for a set of Sample Points sp
        */
        template<size_t K>
        Polynomial<double,K> LagrangeBasis (std::array<double, K> sp_x, std::array<double, K> sp_fx) {
            // for all x_values in sp_x at respective index i
            //      build l_i by first creating a Polynom<2> 
            //      as x / x_i-x_j, -x_j / x_i - x_j for all x-es, 
            //      where x_i != x_j
            //      !: if x_i == x_j : Value of multiplier is 1, i.e. ommitted from calculation
            // Calculate P(x) as the sum of f_i * l_i 
            // using respective function values for x_i
            
            std::array<Polynomial<double,K>,sp_x.size()> l;
            for (size_t i = 0; i < sp_x.size(); ++i)
            {
                std::array<Polynomial<double, 2>, sp_x.size()-1> stepwise_polynomials;
                for (size_t j = 0, pos = 0; j < sp_x.size(); ++j)
                {
                    if(j != i)
                    {
                        stepwise_polynomials[pos] = Polynomial<double,2>({ -sp_x[j] / (sp_x[i]-sp_x[j]) , 1/sp_x[i]});
                        ++pos;
                    }
                }
                Polynomial<double, K> lagrange_polynomial = Recursive::SetProductEqualDegree(stepwise_polynomials);
                l[i] = lagrange_polynomial;
            }
            Polynomial<double,K> interpolation;
            for (size_t i = 0; i < sp_x.size(); ++i)
                interpolation += sp_fx[i] * l[i];

            return interpolation;
        };

    }
};


#endif