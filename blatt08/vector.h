#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

#include "expression_templates.h"

class Vector{
  std::vector<double> _data;
public:
  Vector(unsigned int length)
    : _data(length) {}

  Vector(const Vector&) = default;

  // Constructor from Unary Expression Template
  template<typename F, typename A>
  Vector(UnaryExpr<F,A> const& expr)
  {
    _data.reserve(expr.size());
    for(int i = 0; i < expr.size(); ++i)
      _data[i] += expr[i];
  }

  // Constructor from Binary Expression Template
  template<typename F, typename A, typename B>
  Vector(BinaryExpr<F,A,B> const& expr)
  {
    _data.reserve(expr.size());
    for(int i = 0; i < expr.size(); ++i)
      _data[i] = expr[i];
  }

  Vector& operator=(const Vector&) = default;

  // Assignment of Unary Expression Template
  template<typename F, typename A>
  Vector& operator= (UnaryExpr<F,A> const& expr)
  {
    _data(expr.size_());
    for(int i = 0; i < expr.size_(); ++i)
      _data[i] += expr[i];
    return *this;
  }

  // Assignment of Binary Expression Template
  template<typename F, typename A, typename B>
  Vector& operator= (BinaryExpr<F,A,B> const& expr)
  {
    _data(expr.size_());
    for(int i = 0; i < expr.size_(); ++i)
      _data[i] += expr[i];
    return *this;
  }
  
  // Compound assignment of Unary Expression Template
  template<typename F, typename A>
  Vector& operator+= (UnaryExpr<F,A> const& expr)
  {
    for(int i = 0; i < expr.size_(); ++i)
      _data[i] += expr[i];
    return *this;
  }

  // Compound assignment of Binary Expression Template
  template<typename F, typename A, typename B>
  Vector& operator+= (BinaryExpr<F,A,B> const& expr)
  {
    for(int i = 0; i < expr.size_(); ++i)
      _data[i] += expr[i];
    return *this;
  }

  Vector(std::initializer_list<double> l)
    : _data(l)
  {}

  Vector& operator=(double d){
    _data.assign(_data.size(), d);
    return *this;
  }

  // only works with scalar product implementation
  //double two_norm() const{
  //  return std::sqrt((*this) * (*this));
  //}

  double& operator[](unsigned int i){
    return _data[i];
  }

  double operator[](unsigned int i) const{
    return _data[i];
  }

  unsigned int size() const{
    return _data.size();
  }
};

std::ostream& operator <<(std::ostream& str, const Vector& v){
  if(v.size() == 0){
    str << "Vector of size 0";
    return str;
  }
  str << "[" << v[0];
  for(size_t i=1; i<v.size(); ++i){
    str << ", " << v[i];
  }
  str << "]";
  return str;
}

#endif
