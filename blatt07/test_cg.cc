#include <iostream>

#include "src/vector.h"
#include "src/matrix.h"
#include "src/cg.h"
#include "src/lu.h"

int main ()
{
    std::vector<std::vector<double>> mat_data = {{2,-1,0},{-1,2,-1},{0,-1,2}};

    Matrix m (mat_data);
    Vector b ({1.,1.,1.});

    Vector x(3);
    Vector y(3);

    LU lu(m.rows());
    lu.decompose(m);
    lu.solve(b, x);
    
    CGSolver<Matrix,Vector> cg (100, 1e-13);
    y = cg.solve(m,b);

    bool eq = true;
    for (int i = 0; i < y.size(); ++i)
        if(std::abs(x(i) - y(i)) > 1e-13)
            eq = false;
    if (eq)
        std::cout << "Equal results." << std::endl;
}
