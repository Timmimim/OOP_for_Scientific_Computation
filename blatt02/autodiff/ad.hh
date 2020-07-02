#include <cmath>
#include <stdexcept>
#include <iostream>

#ifndef AUTO_DIFF
#define AUTO_DIFF

namespace Ad
{
    class SimpleAd
    {
    public:
      explicit SimpleAd(double val)
        : SimpleAd(val, 1.0)
      {}

      SimpleAd(double val, double deriv)
        : val_(val), deriv_(deriv)
      {}

      double value() const {
        return val_;
      }

      double derivative() const {
        return deriv_;
      }

      // arithmetic operations with other SimpleAd
      SimpleAd operator+(const SimpleAd& other) const
      {
        return SimpleAd(this->value()+other.value(), 
                        this->derivative()+other.derivative());
      }

      SimpleAd operator-(const SimpleAd& other) const
      {
        return SimpleAd(this->value()-other.value(), 
                        this->derivative()-other.derivative());
      }

      SimpleAd operator*(const SimpleAd& other) const
      {
        return SimpleAd(this->value()*other.value(), 
                        this->value()*other.derivative() + other.value()*this->derivative());
      }

      SimpleAd operator/(const SimpleAd& other) const
      {
        return SimpleAd(this->value()/other.value(), 
                    (this->value()*other.derivative() - other.value()*this->derivative()) / std::pow(this->value(),2)
                  );
      }

      // explicit conversion to double
      explicit operator double() const {
        return val_;
      }

    private:
      double val_;
      double deriv_;

    };

  // arithmetic operations with double and math functions
  SimpleAd operator+(const SimpleAd& left, const double right)
  {
    return SimpleAd(left.value() + right, left.derivative());
  }

  SimpleAd operator+(const double left, const SimpleAd& right)
  {
    return SimpleAd(left + right.value(), right.derivative());
  }
  
  SimpleAd operator-(const SimpleAd& left, const double right)
  {
    return SimpleAd(left.value() - right, left.derivative());
  }

  SimpleAd operator-(const double left, const SimpleAd& right)
  {
    return SimpleAd(left - right.value(), right.derivative());
  }

  SimpleAd operator*(const SimpleAd& left, const double right)
  {
    return SimpleAd(left.value()*right, left.derivative()*right);
  }

  SimpleAd operator*(const double left, const SimpleAd& right)
  {
    return SimpleAd(left*right.value(), left*right.derivative());
  }

  SimpleAd sin(const SimpleAd& x)
  {
    return SimpleAd(std::sin(x.value()), x.derivative() * std::cos(x.value()));
  }

}

#endif