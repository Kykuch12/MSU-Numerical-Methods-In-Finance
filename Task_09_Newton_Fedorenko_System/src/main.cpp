#include <iostream>
#include "newton.hpp"

int main(){
    double x0 = 1.0;
    double y0 = 1.0;
    double x_sol, y_sol;
    int iter = 0;
    newton_fedorenko(x0, y0, &x_sol, &y_sol, &iter);
    std::cout << "x_sol = " << x_sol << ", y_sol = " << y_sol << ", iter = " << iter << std::endl;
    double err = error(x_sol, y_sol);
    std::cout << "error = " << err << std::endl;
    std::cout << "f1(x_sol, y_sol) = " << f1(x_sol, y_sol) << ", f2(x_sol, y_sol) = " << f2(x_sol, y_sol) << std::endl;
    return 0;
}