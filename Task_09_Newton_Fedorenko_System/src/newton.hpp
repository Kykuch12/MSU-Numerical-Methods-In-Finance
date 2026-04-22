#ifndef NEWTON_HPP
#define NEWTON_HPP

#define MAX_ITERATIONS 100
#define EPS_NORM_SYSTEM 1e-10
#define MAX_TAU_ITERATIONS 30
// Нелинейные функции системы уравнений
double f1(double x, double y);
double f2(double x, double y);

// Частные производные
double df1_dx(double x, double y);
double df1_dy(double x, double y);
double df2_dx(double x, double y);
double df2_dy(double x, double y);

// Alpha_1,2, нормы градиентов функций f_1,2
double alpha1(double x, double y);
double alpha2(double x, double y);

// ||F(x_n)||_weighted
double norm_system(double x, double y);

// Метод Ньютона с модификацией Федоренко
int newton_fedorenko(double x, double y, double *x_sol, double *y_sol, int *iter);

// Расчёт ошибки
double error(double x, double y);

#endif