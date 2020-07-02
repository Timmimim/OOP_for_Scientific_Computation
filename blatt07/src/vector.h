#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <cassert>

class Vector{
  std::vector<double> _data;
public:
  Vector(unsigned int length)
    : _data(length) {}

  Vector(const Vector&) = default;

  Vector(Vector&&) = default;

  Vector& operator=(const Vector&) = default;

  Vector& operator=(Vector&&) = default;

  Vector(std::initializer_list<double> l)
    : _data(l)
  {}

  Vector& operator=(double d){
    _data.assign(_data.size(), d);
    return *this;
  }

  double dot(const Vector& y) const{
    assert((*this).size() == y.size());
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

  Vector& operator+=(const Vector& y){
    assert((*this).size() == y.size());
    for(size_t i=0; i<(*this).size(); ++i){
      (*this)(i) += y(i);
    }
    return *this;
  }

  Vector& operator+=(Vector&& y){
    assert((*this).size() == y.size());
    for(size_t i=0; i<(*this).size(); ++i){
      (*this)(i) += y(i);
    }
    return *this;
  }

  Vector& operator-=(const Vector& y){
    assert((*this).size() == y.size());
    for(size_t i=0; i<(*this).size(); ++i){
      (*this)(i) -= y(i);
    }
    return *this;
  }

  Vector& operator-=(Vector&& y){
    assert((*this).size() == y.size());
    for(size_t i=0; i<(*this).size(); ++i){
      (*this)(i) -= y(i);
    }
    return *this;
  }
};

Vector operator+(const Vector& x, const Vector& y){
  assert(x.size() == y.size());
  Vector tmp(x.size());
  for(size_t i=0; i<x.size(); ++i){
    tmp(i) = x(i)+y(i);
  }
  return std::move(tmp);
}

Vector operator+(Vector&& x, const Vector& y){
  assert(x.size() == y.size());
  for(size_t i=0; i<x.size(); ++i){
    x(i) = x(i)+y(i);
  }
  return std::move(x);
}

Vector operator+(const Vector& x, Vector&& y){
  assert(x.size() == y.size());
  for(size_t i=0; i<y.size(); ++i){
    y(i) = x(i)+y(i);
  }
  return std::move(y);
}

Vector operator-(const Vector& x, const Vector& y){
  assert(x.size() == y.size());
  Vector tmp(x.size());
  for(size_t i=0; i<x.size(); ++i){
    tmp(i) = x(i)-y(i);
  }
  return std::move(tmp);
}

Vector operator-(Vector&& x, const Vector& y){
  assert(x.size() == y.size());
  for(size_t i=0; i<x.size(); ++i){
    x(i) = x(i)-y(i);
  }
  return std::move(x);
}

Vector operator-(const Vector& x, Vector&& y){
  assert(x.size() == y.size());
  for(size_t i=0; i<y.size(); ++i){
    y(i) = x(i)-y(i);
  }
  return std::move(y);
}

Vector operator*(const double& x, const Vector& y){
  Vector tmp(y.size());
  for(size_t i=0; i<y.size(); ++i){
    tmp(i) = x*y(i);
  }
  return std::move(tmp);
}

Vector operator*(const double& x, Vector&& y){
  for(size_t i=0; i<y.size(); ++i){
    y(i) *= x;
  }
  return std::move(y);
}

std::ostream& operator <<(std::ostream& str, const Vector& v){
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
