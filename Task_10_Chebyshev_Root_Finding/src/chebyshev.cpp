#include <cstdio>

#include "chebyshev.hpp"

int chebyshev(int m, double a, double x0, double *x_sol, double eps, int max_iter, int *iter){
    double x = x0;
    double x_prev;
    
    // Если a = 0, то корень 0
    if (fabs(a) < eps){
        *x_sol = 0.0;
        *iter = 0;
        return 0;
    }
    // Если m = 1, то корень a
    if (m == 1){
        *x_sol = a;
        *iter = 0;
        return 0;
    }
    
    for (*iter = 0; *iter < max_iter; (*iter)++){
        x_prev = x;
        
        double t = 1.0 - a / pow(x, m);
        // double t = 1.0 - a * exp(-x);
        
        // Вычисляем коэффициенты Чебышева

        // Для f(x) = x^m - a
        double c1 = -1.0 / m;
        double c2 = (1.0 - m) / (2.0 * m * m);
        double c3 = -(1.0 - m) * (1.0 - 2.0 * m) / (6.0 * m * m * m);
        double c4 = (1.0 - m) * (1.0 - 2.0 * m) * (1.0 - 3.0 * m) / (24.0 * m * m * m * m);
        double c5 = -(1.0 - m) * (1.0 - 2.0 * m) * (1.0 - 3.0 * m) * (1.0 - 4.0 * m) /  (120.0 * m * m * m * m * m);

        x = x * (1.0 + t * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5)))));

        // Для f(x) = exp(x) - a
        // double c1 = -1.0;
        // double c2 = - 1.0 / 2.0;
        // double c3 = - 1.0 / 3.0;
        // double c4 = - 1.0 / 4.0;
        // double c5 = - 1.0 / 5.0;

        // x = x + t * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5))));
        
        // Сходимость по х: Насколько в eps окрестности двигаемся? М.б. уже хватит?
        if (fabs(x - x_prev) < eps){
            *x_sol = x;
            return 0;
        }
        // Проверка сходимости по невязке
        double resid = residual(m, a, x);
        if (fabs(resid) < eps){
            *x_sol = x;
            return 0;
        }
    }
    *x_sol = x;
    return -1;
}

double residual(int m, double a, double x){
    return fabs(pow(x, m) - a);
    // (void) m;
    // return fabs(exp(x) - a) + 0*m;
}