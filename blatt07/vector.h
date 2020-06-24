#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

class Vector{
  std::vector<double> _data;
public:
  Vector(unsigned int length)
    : _data(length) {}

  Vector(const Vector& other) = default;

  Vector(std::initializer_list<double> l)
    : _data(l)
  {}

  Vector& operator=(double d){
    _data.assign(_data.size(), d);
    return *this;
  }

  double dot(const Vector y) const{
    double sum = 0.;
    for (size_t i = 0; i < _data.size(); ++i){
      sum += _data[i] * y(i);
    }
    return sum;    
  }

  double two_norm() const{
    return std::sqrt(this->dot(*this));
  }

  double& operator()(unsigned int i){
    return _data[i];
  }

  const double& operator()(unsigned int i) const{
    return _data[i];
  }

  unsigned int size() const{
    return _data.size();
  }

  Vector& operator+=(const Vector y){
    for(size_t i=0; i<(*this).size(); ++i){
      (*this)(i) += y(i);
    }
    return *this;
  }

  Vector& operator-=(const Vector y){
    for(size_t i=0; i<(*this).size(); ++i){
      (*this)(i) -= y(i);
    }
    return *this;
  }
};

Vector operator+(const Vector x, const Vector y){
  Vector tmp(x.size());
  for(size_t i=0; i<x.size(); ++i){
    tmp(i) = x(i)+y(i);
  }
  return tmp;
}

Vector operator-(const Vector x, const Vector y){
  Vector tmp(x.size());
  for(size_t i=0; i<x.size(); ++i){
    tmp(i) = x(i)-y(i);
  }
  return tmp;
}

Vector operator*(const double& x, const Vector y){
  Vector tmp(y.size());
  for(size_t i=0; i<y.size(); ++i){
    tmp(i) = x*y(i);
  }
  return tmp;
}

std::ostream& operator <<(std::ostream& str, const Vector v){
  if(v.size() == 0){
    str << "Vector of size 0";
    return str;
  }
  str << "[" << v(0);
  for(size_t i=1; i<v.size(); ++i){
    str << ", " << v(i);
  }
  str << "]";
  return str;
}

#endif