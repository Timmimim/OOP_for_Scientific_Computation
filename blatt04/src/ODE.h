#ifndef ODE_H
#define ODE_H

#include <array>

template <std::size_t N>
class ODE {
public:
    virtual std::array<double,N> f();
private:
    /**
     * TODO: Implement me.
     */
};

#endif