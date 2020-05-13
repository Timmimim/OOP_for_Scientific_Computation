#include "vector.h"
#include "matrix.h"
#include "lu.h"

#include <iostream>


int main() {

    /**
     * m = ((2,-1,0),(-1,2,-1),(0,-1,2))
     * b = (1,1,1)
     * 
     * Ax = b   is to be solved for Vector x
     */
    Matrix m ({{2,-1,0},{-1,2,-1},{0,-1,2}});
    
    double elements[3] = {1.,1.,1.};
    Vector b (elements, 3);
    
    // skip assertions; 
    // we wrote main and hardcoded m and b; we trust ourselves to ensure dimensions match here.

    // use a variable for matrix and vector sizes, deduced from input vector- and matrix dimensions
    size_t dim = b.size();

    // target vector x to solve for
    Vector x(dim);
    
    /**
     * terminal output
     * validate correctness of initial matrix A and vector b
     * 
     * wrapped in own scope to make it collapsible and easy to deactivate
     */
    /*
    { // validate correctness of m (i.e. A) and b
        std::cout << "\n";
        std::cout << "\nMatrix m (=A):\n";
        for (size_t i = 0; i < m.rows(); ++i)
        {
        for (size_t j = 0; j < m.cols(); ++j)
        {
            std::cout << m(i,j) << "  ";
        }
        std::cout << "\n";
        }
        
        std::cout << "\nVector b:\n";
        for (size_t r = 0; r < b.size(); ++r)
        {
            std::cout << b(r) << "\n";
        }
    }
    */

    LU lu(m.rows());
    lu.decompose(m);
    lu.solve(b, x);

    std::cout << "\nMy result for x:\n";
    for (size_t r = 0; r < x.size(); ++r)
    {
        std::cout << x(r) << "\n";
    }

    Vector r(3);
    Vector mx(3);
    m.mv(x, mx);
    r = b - mx;

    std::cout << "\nResidual:\n";
    for (size_t s = 0; s < mx.size(); ++s)
    {
        std::cout << r(s) << "\n";
    }
}