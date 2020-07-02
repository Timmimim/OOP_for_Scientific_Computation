#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <array>
#include <type_traits>
#include <cassert>
#include <cmath>

template<typename T, size_t N>
class Polynomial
{
public:
    Polynomial() 
        : _coefficients(std::array<T,N+1>()) {
            static_assert(std::is_arithmetic<T>::value, "Only arithmetic parameters permitted as coefficients.");
        };

    Polynomial(std::array<T,N+1>& coeff)
        : _coefficients(coeff){
            static_assert(std::is_arithmetic<T>::value, "Only arithmetic parameters permitted as coefficients.");
            assert(std::abs(coeff[N]) >= 1e-13);
        };

    /**
     * TODO: Rule of 5.
     */
    ~Polynomial() {};

    Polynomial (const Polynomial& other)
    {
        _coefficients = other._coefficients;
    }

    Polynomial operator= (const Polynomial& other)
    {
        _coefficients = other._coefficients;
        return *this;
    }

    //==============================================
    //==============================================
    //==============================================
    //==============================================

    double operator() (double x_val) const
    {
        double res = 0.;
        for (size_t i = 0; i < _coefficients.size(); ++i)
            res += _coefficients[i] * std::pow(x_val, i);
        return res;
    }

    template <typename T2, size_t M>
    auto operator+= (const Polynomial<T2,M>& other)
    -> typename std::enable_if<(M<=N), Polynomial<T,N>>::type
    {
        for(size_t i = 0; i < other.size(); ++i)
        {
            _coefficients[i] += other(i);
        }
        return *this;
    };

    template <typename T2, size_t M>
    auto operator-= (const Polynomial<T2,M>& other)
    -> typename std::enable_if<(M<=N), Polynomial<T,N>>::type
    {
        for(size_t i = 0; i < other.size(); ++i)
        {
            _coefficients[i] -= other(i);
        }
        return *this;
    }

    Polynomial operator*= (const T& alpha)
    {
        for(auto &coeff : _coefficients)
        {
            coeff *= alpha;
        }
        return *this;
    }

    T& coeff (unsigned int exponent)
    {
        assert(exponent < _coefficients.size());
        return _coefficients[exponent];
    }

    const T& coeff (unsigned int exponent) const
    {
        assert(exponent < _coefficients.size());
        return _coefficients[exponent];
    }

    Polynomial<T,N-1> trim ()
    {   
        std::array<T,N> coefficients;
        if(std::abs(_coefficients[N]) <= 1e-13)
        {
            std::copy(  _coefficients.begin(), 
                        _coefficients.end() - 1,
                        coefficients.begin());
        }
        else
        {
            std::cout << _coefficients[N] << std::endl;
            throw;
        }
        
        return Polynomial<T,N-1> (coefficients);
    }

    size_t size()
    {
        return N;
    }

    template<typename TYPE, size_t SIZE>
    friend std::ostream& operator<<( std::ostream&, const Polynomial<TYPE,SIZE>& );

private:
    std::array<T,N+1> _coefficients;
};


/*
=====================================================================================
===================== Free Operators for Class Polynomial ===========================
=====================================================================================
*/


template<typename T, size_t N>
std::ostream& operator<< (std::ostream& os, const Polynomial<T,N>& poly)
{
    assert (N >= 0);
    int i = N;
    os << poly.coeff(i) << "x^" << i;
    if(N >= 0)
    {
        for (int i = ((int)N)-1; i > 0; --i)
        {
            if (poly.coeff(i) > 0)
                os << " + " << std::abs(poly.coeff(i)) << "x^" << i;
            else if (poly.coeff(i) < 0)
                os << " - " << std::abs(poly.coeff(i)) << "x^" << i;
            else {}
        }
        if (poly.coeff(0) > 0) os << " + " << poly.coeff(0) << std::endl;
        else if (poly.coeff(0) < 0) os << " - " << std::abs(poly.coeff(0)) << std::endl;
        else os << std::endl;
    }
    else os << std::endl;
    return os;
}

template<typename T, size_t N>
typename std::enable_if<std::is_floating_point<T>::value, Polynomial<double, N-1>>::type
differentiate (Polynomial<T,N> to_diff)
{
    assert (N > 0);
    auto res = Polynomial<double, N-1>();
    for (size_t i = 1; i <= N; ++i)
    {
        size_t power = i;
        res.coeff(i-1) = to_diff.coeff(i) * power;
    }
    return res;
}

template<typename T, size_t N>
typename std::enable_if<std::is_integral<T>::value, Polynomial<int, N-1>>::type
differentiate (Polynomial<T,N> to_diff)
{
    assert (N > 0);
    auto res = Polynomial<int, N-1>();
    for (size_t i = 1; i <= N; ++i)
    {
        size_t power = i;
        res.coeff(i-1) = to_diff.coeff(i) * power;
    }
    return res;
}

template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_floating_point<T1>::value || std::is_floating_point<T2>::value, Polynomial<double,std::max(M,N)>>::type
operator+ (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<double,std::max(M,N)>();
    for (size_t i = 0; i<=std::max(M,N); ++i)
    {
        if (i > M) res.coeff(i) = second.coeff(i);
        else
        if (i > N) res.coeff(i) = first.coeff(i);
        else
        {
            res.coeff(i) = first.coeff(i) + second.coeff(i);
        }
    }
    return res;
}

template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_integral<T1>::value && std::is_integral<T2>::value, Polynomial<int,std::max(M,N)>>::type
operator+ (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<int,std::max(M,N)>();
    for (size_t i = 0; i<=std::max(M,N); ++i)
    {
        if (i > M) res.coeff(i) = second.coeff(i);
        else
        if (i > N) res.coeff(i) = first.coeff(i);
        else
        {
            res.coeff(i) = first.coeff(i) + second.coeff(i);
        }
    }
    return res;
}

template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_floating_point<T1>::value || std::is_floating_point<T2>::value, Polynomial<double,std::max(M,N)>>::type
operator- (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<double,std::max(M,N)>();
    for (size_t i = 0; i<=std::max(M,N); ++i)
    {
        if (i > M) res.coeff(i) = -second.coeff(i);
        else
        if (i > N) res.coeff(i) = first.coeff(i);
        else
        {
            res.coeff(i) = first.coeff(i) - second.coeff(i);
        }
    }
    return res;
}

template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_integral<T1>::value && std::is_integral<T2>::value, Polynomial<int,std::max(M,N)>>::type
operator- (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<int,std::max(M,N)>();
    for (size_t i = 0; i<=std::max(M,N); ++i)
    {
        if (i > M) res.coeff(i) = -second.coeff(i);
        else
        if (i > N) res.coeff(i) = first.coeff(i);
        else
        {
            res.coeff(i) = first.coeff(i) - second.coeff(i);
        }
    }
    return res;
}


template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_floating_point<T1>::value || std::is_floating_point<T2>::value, Polynomial<double, M+N>>::type
operator* (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<double, M+N>();
    for (size_t i = 0; i <= M; ++i)
    {
        for (size_t j = 0; j <= N; j++)
        {
            res.coeff(i+j) += first.coeff(i) * second.coeff(j);
        }
    }
    return res;
}

template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_integral<T1>::value && std::is_integral<T2>::value, Polynomial<int, M+N>>::type
operator* (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<int, M+N>();
    for (size_t i = 0; i <= M; ++i)
    {
        for (size_t j = 0; j <= N; j++)
        {
            res.coeff(i+j) += first.coeff(i) * second.coeff(j);
        }
    }
    return res;
}

#endif