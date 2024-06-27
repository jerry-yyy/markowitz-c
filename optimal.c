#include "markowitz.h"
#include "optimal.h"


double **monte_carlo(int num_portfolios, double *mean_returns, double **cov_matrix, int num_assets) {
    double **result = (double **)calloc(num_portfolios, sizeof(double *) * NUM_COLS);

    double risk_free_rate = 0.0;
    double sharp_ritio = 0.0;

    srand((unsigned int)time(NULL));

    double *weights = (double *)calloc(num_assets, sizeof(double));

    // simulation
    for (int i = 0; i < num_portfolios; i++) {
        // 生成随机weights并归一化。
        double sum = 0.0;
        for (int j = 0; j < num_assets; j++) {
            weights[i] = (double) rand() / RAND_MAX;
            sum += weights[i];
        }
        for (int j = 0; j < num_assets; j++) {
            weights[i] /= sum;
        }
        
        // return
        result[i][0] = portfolio_annulised_return(weights, mean_returns, num_assets);
        // std
        result[i][1] = portfolio_annulised_std(weights, cov_matrix, num_assets);
        // sharp ratio
        result[i][2] = (result[i][0] - risk_free_rate) / result[i][1];
    }

    free(weights);

    return result;
}