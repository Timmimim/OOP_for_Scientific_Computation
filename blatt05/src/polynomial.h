#include <iostream>
#include <array>
#include <type_traits>
#include <cassert>

template<typename T, size_t N, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Polynomial
{
public:
    Polynomial() 
        : _coefficients(std::array<T,N>()) {};

    Polynomial(std::array<T,N> coeff)
        : _coefficients(coeff){}

    /**
     * TODO: Rule of 5.
     */
    //========================

    T& operator() (unsigned int exponent)
    {
        assert(exponent < _coefficients.size());
        return _coefficients[exponent];
    }

    const T& operator() (unsigned int exponent) const
    {
        assert(exponent < _coefficients.size());
        return _coefficients[exponent];
    }

    Polynomial operator*= (const T& alpha)
    {
        for(auto &coeff : _coefficients)
        {
            coeff *= alpha;
        }
        return *this;
    }

    template<typename TYPE, size_t SIZE>
    friend std::ostream& operator<<( std::ostream&, const Polynomial<TYPE,SIZE>& );

private:
    std::array<T,N> _coefficients;
};


/*
=====================================================================================
===================== Free Operators for Class Polynomial ===========================
=====================================================================================
*/


template<typename T, size_t N>
std::ostream& operator<< (std::ostream& os, const Polynomial<T,N>& poly)
{
    int i = N-1;
    os << poly(i) << "x^" << i;
    for (int i = N-2; i > 0; --i)
    {
        if (poly(i) > 0)
            os << " + " << std::abs(poly(i)) << "x^" << i;
        else if (poly(i) < 0)
            os << " - " << std::abs(poly(i)) << "x^" << i;
        else {}
    }
    if (poly(0) > 0) os << " + " << poly(0) << std::endl;
    else if (poly(0) < 0) os << " - " << std::abs(poly(0)) << std::endl;
    else os << std::endl;
    return os;
}

template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_floating_point<T1>::value || std::is_floating_point<T2>::value, Polynomial<double,std::max(M,N)>>::type
operator+ (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<double,std::max(M,N)>();
    for (size_t i = 0; i<std::max(M,N); ++i)
    {
        if (i >= M) res(i) = second(i);
        else
        if (i >= N) res(i) = first(i);
        else
        {
            res(i) = first(i) + second(i);
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
    for (size_t i = 0; i<std::max(M,N); ++i)
    {
        if (i >= M) res(i) = second(i);
        else
        if (i >= N) res(i) = first(i);
        else
        {
            res(i) = first(i) + second(i);
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
    for (size_t i = 0; i<std::max(M,N); ++i)
    {
        if (i >= M) res(i) = -second(i);
        else
        if (i >= N) res(i) = first(i);
        else
        {
            res(i) = first(i) - second(i);
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
    for (size_t i = 0; i<std::max(M,N); ++i)
    {
        if (i >= M) res(i) = -second(i);
        else
        if (i >= N) res(i) = first(i);
        else
        {
            res(i) = first(i) - second(i);
        }
    }
    return res;
}


template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_floating_point<T1>::value || std::is_floating_point<T2>::value, Polynomial<double, M+N-1>>::type
operator* (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<double, M+N-1>();
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i+j) += first(i) * second(j);
        }
    }
    return res;
}

template<typename T1, size_t M, 
        typename T2, size_t N>
typename std::enable_if<std::is_integral<T1>::value && std::is_integral<T2>::value, Polynomial<int, M+N-1>>::type
operator* (Polynomial<T1,M> first, Polynomial<T2,N> second)
{
    auto res = Polynomial<int, M+N-1>();
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i+j) += first(i) * second(j);
        }
    }
    return res;
}