#include <cmath>
#include <stdexcept>
#include <iostream>

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
        // TODO Implement me!
      }

      SimpleAd operator-(const SimpleAd& other) const
      {
        // TODO Implement me!
      }

      SimpleAd operator*(const SimpleAd& other) const
      {
        // TODO Implement me!
      }

      SimpleAd operator/(const SimpleAd& other) const
      {
        // TODO Implement me!
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
    // TODO Implement me!
  }

  SimpleAd operator+(const double left, const SimpleAd& right)
  {
    // TODO Implement me!
  }

  SimpleAd operator*(const SimpleAd& left, const double right)
  {
    // TODO Implement me!
  }

  SimpleAd operator*(const double left, const SimpleAd& right)
  {
    // TODO Implement me!
  }

  SimpleAd sin(const SimpleAd& x)
  {
    // TODO Implement me!
  }

}
