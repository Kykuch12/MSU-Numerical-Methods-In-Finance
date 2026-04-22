#include "newton.hpp"
#include <cmath>
#include <iostream>

// Нелинейные функции системы уравнений
double f1(double x, double y){
    return pow(x, 5.0) + pow(y, 4.0) - 2.0;
}
double f2(double x, double y){
    return pow(x-2.0, 3.0) + pow(y-3.0, 3.0) + 16.0;
}

// Частные производные
double df1_dx(double x, double y){
    (void) y;
    return 5.0 * pow(x, 4.0);
}
double df1_dy(double x, double y){
    (void) x;
    return 4.0 * pow(y, 3.0);
}
double df2_dx(double x, double y){
    (void) y;
    return 3.0 * pow(x-2.0, 2.0);
}
double df2_dy(double x, double y){
    (void) x;
    return 3.0 * pow(y-3.0, 2.0);
}

// Alpha_1,2, нормы градиентов функций f_1,2
double alpha1(double x, double y){
    double dx = df1_dx(x, y);
    double dy = df1_dy(x, y);
    return sqrt(dx * dx + dy * dy);
}
double alpha2(double x, double y){
    double dx = df2_dx(x, y);
    double dy = df2_dy(x, y);
    return sqrt(dx * dx + dy * dy);
}

// ||F(x_n)||_weighted
double norm_system(double x, double y){
    // Значения f_1,2 в точке
    double f1_value = f1(x, y);
    double f2_value = f2(x, y);
    // Значения alpha_1,2 в точке
    double a1 = alpha1(x, y);
    double a2 = alpha2(x, y);
    return sqrt(pow(f1_value / a1, 2.0) + pow(f2_value / a2, 2.0));
}

// Поиск Δ_n
double delta_n(double x, double y, double *delta1, double *delta2){
    // Матрица Якоби в точке
    double J_11 = df1_dx(x, y);
    double J_12 = df1_dy(x, y);
    double J_21 = df2_dx(x, y);
    double J_22 = df2_dy(x, y);
    // Якобиан
    double det = J_11 * J_22 - J_12 * J_21;
    if (fabs(det) < 1e-15){
        std::cout << "Якобиан = 0" << std::endl;
        return 1;
    } 
    // Правая часть СЛАУ
    double b1 = -f1(x, y);
    double b2 = -f2(x, y);
    // Поиск Δ_n
    *delta1 = (J_22 * b1 - J_21 * b2) / det;
    *delta2 = (-J_12 * b1 + J_11 * b2) / det;
    return 0;
}

int newton_fedorenko(double x0, double y0, double *x_sol, double *y_sol, int *iter){
    double x_curr = x0;
    double y_curr = y0;

    double norm_curr;

    for (int i = 0; i <= MAX_ITERATIONS; i++){

        norm_curr = norm_system(x_curr, y_curr);

        if (norm_curr < EPS_NORM_SYSTEM){
            *x_sol = x_curr;
            *y_sol = y_curr;
            *iter = i;
            return 0;
        }

        double delta1, delta2;
        if (delta_n(x_curr, y_curr, &delta1, &delta2) != 0){
            std::cout << "Матрица вырождена" << std::endl;
            return 1;
        }

        double x_new, y_new;
        double norm_new;
        
        double tau = 1.0;
        bool tau_founded = false;

        for (int j = 0; j <= MAX_TAU_ITERATIONS; j++){
            x_new = x_curr + tau * delta1;
            y_new = y_curr + tau * delta2;

            norm_new = norm_system(x_new, y_new);

            if (norm_new < norm_curr){
                tau_founded = true;
                break;
            }
            tau *= 0.5;
        }

        if (!tau_founded){
                std::cout << "tau не нашлось" << std::endl;
                return 1;
            }

        x_curr = x_new;
        y_curr = y_new;
    }

    std::cout << "Превышено максимальное число итераций" << std::endl;
    *x_sol = x_curr;
    *y_sol = y_curr;
    *iter = MAX_ITERATIONS;
    return 1;
}

double error(double x, double y){
    return sqrt(f1(x, y)*f1(x, y) + f2(x, y)*f2(x, y));
}