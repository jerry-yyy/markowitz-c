#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <time.h>


#define NUM_COLS 3  // return, std, sharp ratio.

// 函数声明
double **monte_carlo(int num_portfolios, double *mean_returns, double **cov_matrix, int num_assets);

#endif // OPTIMAL_H
