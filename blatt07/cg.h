#pragma once

#include <cstddef>

template<typename M, typename V>
class CGSolver{
    public:
    CGSolver(size_t maxIt_, double eps_)
        : maxIt(maxIt_), eps(eps_) { }

    V solve(const M& A, const V& y){
        V x(y.size());
        x = 0.;
        
        V r = y - A * x;

        V p = r;
        
        for (size_t i = 0; i < maxIt; i++)
        {
            const auto alpha = r.dot(r) / p.dot(A * p);
            x = x + alpha * p;
            const auto r_new = r - alpha * A * p;
            if (r_new.two_norm() < eps)
                break;
            else{
                const auto beta = r_new.dot(r_new) / r.dot(r);
                p = r_new + beta * p;
                r = r_new;
            }
        }  
        return x;      
    }

    private:
    size_t maxIt;
    double eps;
};
