#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <vector>

class Vector{
public:
  // basic constructor
  Vector(unsigned int length) : _len(length), _data(new double[length]) {}
  
  // destructor
  ~Vector() { delete[] _data; }

  // copy constructor
  Vector(const Vector& other)
  {
    _len = other.size();
    _data = new double[_len];
    std::copy(other._data, other._data+other.size(), _data);
  }

  // move constructor
  Vector(Vector&& other)
  {
    _data = other._data;
    _len = other._len;
    other._data = nullptr;
    other._len = 0;
  }

  Vector(double* data, unsigned int size)
  {
    _len = size;
    _data = new double[_len];
    std::copy(data, data+size, _data);
  }

  // assignment constructor
  Vector& operator= (const Vector& other)
  {
    if (this == &other) return *this;
    if(other.size() != size()){
      delete[] _data;
      _len = other.size();
      _data = new double[_len];
    }
    std::copy(other._data, other._data+other.size(), _data);
    return *this;
  }

  // move assignment constructor
  Vector& operator= (Vector&& other)
  {
    if (this == &other) return *this;
    delete[] _data;
    _data = other._data;
    _len = other._len;
    other._data = nullptr;
    other._len = 0;
    return *this;
  }

  double& operator()(unsigned int i){
    assert(i < _len);
    return _data[i];
  }

  const double& operator()(unsigned int i) const{
    assert(i < _len);
    return _data[i];
  }

  Vector operator+ (const Vector other)
  {
    assert(this->_len == other.size());
    Vector result(_len);
    for(int i = 0; i<result.size(); ++i)
    {
      result(i) = _data[i] + other(i);
    }
    return result;
  }
  
  Vector operator+= (const Vector other)
  {
    assert(this->_len == other.size());
    for(int i = 0; i<_len; ++i)
    {
      _data[i] + other(i);
    }
    return *this;
  }

  Vector operator- (const Vector other)
  {
    assert(this->_len == other.size());
    Vector result(_len);
    for(int i = 0; i<result.size(); ++i)
    {
      result(i) = _data[i] - other(i);
    }
    return result;
  }

  Vector operator-= (const Vector other)
  {
    assert(this->_len == other.size());
    for(int i = 0; i<_len; ++i)
    {
      _data[i] - other(i);
    }
    return *this;
  }

  Vector operator* (const Vector other)
  {
    assert(this->_len == other.size());
    Vector result (this->_len);
    for (int i = 0; i < _len; ++i)
      result(i) = this->_data[i] * other(i);
    return result;
  }

  const double dot (const Vector other) const
  {
    assert(this->_len == other.size());
    double result = 0.;
    for(int i = 0; i < _len; ++i)
    {
      result += _data[i] * other(i);
    }
    return result;
  }

  const double normL1() const
  {
    double norm = 0.;
    for(int i = 0; i<_len; ++i)
      norm += std::abs(_data[i]);
    return norm;
  }

  const double normL2() const
  {
    double norm = 0.;
    for(int i = 0; i<_len; ++i)
      norm += std::pow(_data[i], 2);
    return std::sqrt(norm);
  }

  const double normLInf() const
  {
    double norm = 0.;
    for (size_t i = 0; i < _len; i++)
    {
      double absolute_of_scalar = std::abs(_data[i]);
      if (absolute_of_scalar > norm)
        norm = absolute_of_scalar;

    }
    return norm;
  }

  unsigned int size() const{
    return _len;
  }
  
private:
  unsigned int _len;
  double * _data;
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
