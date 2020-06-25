#include "vector.h"
#include "matrix.h"
#include "expression_templates.h"

int main(){
    Vector a{1, 2, 3};
    Vector b{2, 3, 4};
    Vector c{3, 4, 5};

    Vector t1 = a + b + c;
    Vector t2 = a - a;
    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;

    double alpha = 3.14;
    Vector d{4, 5, 6};
    Vector e{5, 6, 7};
    Vector f{6, 7, 8};

    Vector t3 = alpha * (d + e) + f;
    Vector t4 = (e + d) / 2.;
    std::cout << t3 << std::endl;
    std::cout << t4 << std::endl;

    Vector g{7, 8, 9};
    Vector h{8, 9, 10};
    Vector i{9, 10, 11};

    double t5 = g * h;
    Vector t6 = (g * h) * i;
    std::cout << t5 << std::endl;
    std::cout << t6 << std::endl;

    Vector j{10, 11, 12};
    Vector k{11, 12, 13};
    Vector l{12, 13, 14};

    Matrix M{{{2, -1, 0},
                     {-1, 2, -1},
                     {0, -1, 2}}};

    Vector t7 = j + M * (k - l);
    std::cout << t7 << std::endl;
}