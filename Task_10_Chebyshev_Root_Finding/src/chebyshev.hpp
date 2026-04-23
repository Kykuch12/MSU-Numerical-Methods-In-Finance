#ifndef _CHEBYSHEV_HPP_
#define _CHEBYSHEV_HPP_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cerrno>
#include <iomanip>

#define EPS 1e-15
#define MAX_ITER 1000

int chebyshev(int m, double a, double x0, double *x_sol, double eps, int max_iter, int *iter_count);
double residual(int m, double a, double x);

#endif
