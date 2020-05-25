#include <iostream>
#include <algorithm>

#include "src/ODE.h"
#include "src/SIR.h"
#include "src/ODESolver.h"
#include "src/ImplicitEuler.h"
#include "src/ExplicitEuler.h"

template class ODE<3ul>; 
template class SIR<3ul>; 
template class ODESolver<3ul>; 
template class ExplicitEuler<3ul>; 
template class ImplicitEuler<3ul>; 



int main()
{
    std::cout << "Starting" << std::endl;
    SIR<3> sir_exp(.4,.04,{977,3,0});
    SIR<3> sir_imp(.4,.04,{977,3,0});
    std::cout << "SIR works" << std::endl;
    ExplicitEuler<3> explicit_euler(sir_exp, 0, 1, 100);
    std::cout << "Explicit Constructor works" << std::endl;
    ImplicitEuler<3> implicit_euler(sir_imp, 0, 1, 100);
    std::cout << "Implicit Constructor works" << std::endl;

    auto explicit_solution = explicit_euler.solve();
    std::cout << "Explicit Solver works" << std::endl;
    auto implicit_solution = implicit_euler.solve();
    std::cout << "Implicit Solver works" << std::endl;

    
}