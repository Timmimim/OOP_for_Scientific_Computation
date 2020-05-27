#include <iostream>
#include <array>
#include <type_traits>

template<typename T, size_t N, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Polynomial
{
public:
    Polynomial(std::array<T,N> coeff)
        : _coefficients(coeff){}

    /**
     * TODO: Rule of 5.
     */
    //========================

    double operator() (const unsigned int exponent) const
    {
        assert(exponent < _coefficients.size());
        return _coefficients[exponent];
    }

    double& operator() (const unsigned int exponent)
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

private:
    std::array<T,N> _coefficients;
};