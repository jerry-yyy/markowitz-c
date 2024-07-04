#include "markowitz.h"
#include "optimal.h"


double **monte_carlo(int num_portfolios, double *mean_returns, double **cov_matrix, int num_assets) {
    double **result = (double **)malloc(num_portfolios * sizeof(double *));
    for (int i = 0; i < num_portfolios; i++) {
        result[i] = (double *)calloc(num_assets + NUM_COLS, sizeof(double));
    }
    // hard code. 07.2024, 4.36%. 
    // https://www.macrotrends.net/2016/10-year-treasury-bond-rate-yield-chart
    double risk_free_rate = 0.0436;

    srand((unsigned int)time(NULL));

    double *weights = (double *)calloc(num_assets, sizeof(double));

    // simulation
    for (int i = 0; i < num_portfolios; i++) {
        // 生成随机weights并归一化。
        double sum = 0.0;
        for (int j = 0; j < num_assets; j++) {
            weights[j] = (double) rand() / RAND_MAX;
            sum += weights[j];
        }
        for (int j = 0; j < num_assets; j++) {
            weights[j] /= sum;
            result[i][j] = weights[j];
        }
        
        // return
        result[i][num_assets] = portfolio_annulised_return(weights, mean_returns, num_assets);
        // std
        result[i][num_assets + 1] = portfolio_annulised_std(weights, cov_matrix, num_assets);
        // sharp ratio
        result[i][num_assets + 2] = (result[i][num_assets] - risk_free_rate) / result[i][num_assets + 1];

    }

    free(weights);

    return result;
}