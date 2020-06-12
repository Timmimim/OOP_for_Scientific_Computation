#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <vector>
#include <iostream>

class Vector{
public:
  // basic constructor
  Vector(unsigned int length) : _data(std::vector<double>(length)) {}
  
  // destructor
  ~Vector() { _data.erase(_data.begin(),_data.end());}

  // copy constructor
  Vector(const Vector& other)
  {
    _data = other.data();
  }

  // move constructor
  Vector(Vector&& other)
  {
    _data.swap(other._data);
    other._data.erase(other._data.begin(), other._data.end());
  }

  Vector(double* data, unsigned int size)
  {
    _data = std::vector<double>(data,data+size);
  }

  Vector(std::vector<double>&& data)
  {
    _data.swap(data);
  }

  // assignment constructor
  Vector& operator= (const Vector& other)
  {
    if (this == &other) return *this;
    _data = other._data; 
    return *this;
  }

  // move assignment constructor
  Vector& operator= (Vector&& other)
  {
    if (this == &other) return *this;
    _data.swap(other._data);
    other._data.erase(other._data.begin(), other._data.end());
    return *this;
  }

  double& operator()(unsigned int i){
    assert(i < this->size());
    return _data[i];
  }

  const double& operator()(unsigned int i) const{
    assert(i < this->size());
    return _data[i];
  }

  Vector operator+ (const Vector other)
  {
    assert(this->size() == other.size());
    Vector result(this->size());
    for(int i = 0; i<result.size(); ++i)
    {
      result(i) = _data[i] + other(i);
    }
    return result;
  }
  
  Vector operator+= (const Vector other)
  {
    assert(this->size() == other.size());
    for(int i = 0; i<this->size(); ++i)
    {
      _data[i] += other(i);
    }
    return *this;
  }

  Vector operator- (const Vector other)
  {
    assert(this->size() == other.size());
    Vector result(this->size());
    for(int i = 0; i<result.size(); ++i)
    {
      result(i) = _data[i] - other(i);
    }
    return result;
  }

  Vector operator-= (const Vector other)
  {
    assert(this->size() == other.size());
    for(int i = 0; i<this->size(); ++i)
    {
      _data[i] -= other(i);
    }
    return *this;
  }

  Vector operator* (const Vector other)
  {
    assert(this->size() == other.size());
    Vector result (this->size());
    for (int i = 0; i < this->size(); ++i)
      result(i) = this->_data[i] * other(i);
    return result;
  }

  const double dot (const Vector other) const
  {
    assert(this->size() == other.size());
    double result = 0.;
    for(int i = 0; i < this->size(); ++i)
    {
      result += _data[i] * other(i);
    }
    return result;
  }

  const double normL1() const
  {
    double norm = 0.;
    for(int i = 0; i<this->size(); ++i)
      norm += std::abs(_data[i]);
    return norm;
  }

  const double normL2() const
  {
    double norm = 0.;
    for(int i = 0; i<this->size(); ++i)
      norm += std::pow(_data[i], 2);
    return std::sqrt(norm);
  }

  const double normLInf() const
  {
    double norm = 0.;
    for (size_t i = 0; i < this->size(); i++)
    {
      double absolute_of_scalar = std::abs(_data[i]);
      if (absolute_of_scalar > norm)
        norm = absolute_of_scalar;

    }
    return norm;
  }
  
  std::vector<double> data() const {
    return _data;
  }

  unsigned int size() const{
    return _data.size();
  }
  
private:
  std::vector<double> _data;
};

Vector operator* (const double factor, const Vector& vector)
{
  Vector result(vector.size());
  for(int i = 0; i<result.size(); ++i)
  {
    result(i) = vector(i) * factor;
  }
  return result;
}

// C++ template to print vector container elements 
std::ostream& operator<<(std::ostream& os, const Vector& v) 
{ 
    for (int i = 0; i < v.size(); ++i) { 
        os << v(i); 
        if (i != v.size() - 1) 
            os << ", "; 
    } 
    return os; 
} 

Vector operator* (const Vector& vector, const double factor)
{
  Vector result(vector.size());
  for(int i = 0; i<result.size(); ++i)
  {
    result(i) = vector(i) * factor;
  }
  return result;
}

#endif
