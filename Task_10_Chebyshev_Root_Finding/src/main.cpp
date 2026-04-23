#include <iostream>
#include <cmath>

#include "chebyshev.hpp"

int main(){
    int m = 7; // Степень
    double a = 4; // Коэффициент >= 0
    double epsilon = 1e-10;
    int max_iter = MAX_ITER;
    double x0 = log(a) * 10.0; // Начальное приближение
    
    double x_sol; // Корень
    int iter; // Кол-во итераций

    // Вызов метода Чебышева
    chebyshev(m, a, x0, &x_sol, epsilon, max_iter, &iter);
    
    // Вывод результатов
    double resid = residual(m, a, x_sol);
    std::cout << "x = " << std::setprecision(15) << x_sol << std::endl;
    std::cout << "resid = " << std::setprecision(15) << resid << std::endl;
    std::cout << "iters = " << iter << std::endl;
    return 0;
}
