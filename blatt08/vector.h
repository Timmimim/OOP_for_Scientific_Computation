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

  Vector(const Vector&) = default;

  Vector& operator=(const Vector&) = default;

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
