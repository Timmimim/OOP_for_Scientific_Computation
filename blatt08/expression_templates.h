#pragma once

#include <algorithm>

// unary operations template
template <class Functor, class Arg>
class UnaryExpr
{
    Functor func_;
    Arg const& a_;
    unsigned int size_;

public:
    UnaryExpr(Functor f, Arg argument)
        :   func_(f)
        ,   a_(argument)  
    {};

    // access i-th element of expression
    auto operator[](int i) const
    {
        // apply binary function element-wise 
        return func_(a_[i]);
    }
};

// binary operations template
template <class Functor, class Arg1, class Arg2>
class BinaryExpr
{
    Functor func_;
    Arg1 const& a1_;
    Arg2 const& a2_;
    unsigned int size_;

public:
    BinaryExpr (Functor f, Arg1 argument1, Arg2 argument2, unsigned int size)
        :   func_(f)
        ,   a1_(argument1)
        ,   a2_(argument2)  
        ,   size_(size)
    {}

    // access i-th element of expression
    auto operator[](int i) const
    {
        // apply binary function element-wise 
        return func_(a1_[i], a2_[i]);
    }

    unsigned int size() const
    {
        return size_;
    }
};

template <class Functor, class Arg>
class ScalarProduct
{
    Functor func_;
    Arg const& a1_;
    Arg const& a2_;

public:
    ScalarProduct(Functor f, Arg arg1, Arg arg2)
    :   func_(f)
    ,   a1_(arg1)
    ,   a2_(arg2)
    {}
};

// Binary operation 'Plus'
struct Plus
{
    template <class T1, class T2>
    auto operator() (T1& x, T2& y)
    {
        return x + y;
    }

    template <class T1, class T2>
    const auto operator() (T1 const& x, T2 const& y)
    {
        return x + y;
    }
};

// Binary operation 'Minus'
struct Minus
{
    template <class T1, class T2>
    auto operator() (T1 const& x, T2 const& y)
    {
        return x - y;
    }
};

// Unary operation 'ScalarMult'
struct ScalarMult
{
    template <class T>
    auto operator() (double s, T const& x)
    {
        return s*x;
    }
};

// Unary operation 'ScalarMult'
struct ScalarDiv
{
    template <class T>
    auto operator() (double d, T const& x)
    {
        return x/d;
    }
};

struct VectorProduct
{

};

// Generator Functions

// Generator for Addition
template <typename A, typename B>
BinaryExpr<Plus,A,B> operator+ (A const& a, B const& b)
{
    return BinaryExpr<Plus,A,B> (Plus{}, a, b, std::max(a.size(),b.size()));
}

// Generator for Subtraction
template <typename A, typename B>
BinaryExpr<Minus,A,B> operator- (A const& a, B const& b)
{
    return BinaryExpr<Minus,A,B> (Minus{}, a, b, std::max(a.size(),b.size()));
}

// Generator for Scalar Multiplication
template <typename A>
BinaryExpr<ScalarMult,double,A> operator* (double scalar, A const& a)
{
    return BinaryExpr<ScalarMult,double,A> (ScalarMult{}, scalar, a, a.size());
}

template <typename A>
BinaryExpr<ScalarMult,A,double> operator* (A const& a, double scalar)
{
    return BinaryExpr<ScalarMult,double,A> (ScalarMult{}, scalar, a, a.size());
}

template <typename A>
BinaryExpr<VectorProduct,A,double> operator* (A const& a, A const& b)
{
    assert(a.size() == b.size());
    return BinaryExpr<VectorProduct,double,A> (VectorProduct{}, a, b, a.size());
}

template <typename A>
BinaryExpr<ScalarDiv,A,double> operator/ (A const& a, double divisor)
{
    return BinaryExpr<ScalarDiv,double,A> (ScalarDiv{}, divisor, a, a.size());
}