#include "markowitz.h"
#include "optimal.h"


double **monte_carlo(int num_portfolios, double *mean_returns, double **cov_matrix, int num_assets) {
    double **result = (double **)malloc(num_portfolios * sizeof(double *));
    for (int i = 0; i < num_portfolios; i++) {
        result[i] = (double *)calloc(NUM_COLS, sizeof(double));
    }

    double risk_free_rate = 0.0;

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
        printf("Weights: ");
        for (int j = 0; j < num_assets; j++) {
            weights[i] /= sum;
            printf("%f ", weights[i]);
        }
        printf("\n");
        
        // return
        result[i][0] = portfolio_annulised_return(weights, mean_returns, num_assets);
        // std
        result[i][1] = portfolio_annulised_std(weights, cov_matrix, num_assets);
        // sharp ratio
        result[i][2] = (result[i][0] - risk_free_rate) / result[i][1];
        printf("ret: %f, std: %f, sharp ratio: %f\n", result[i][0], result[i][1], result[i][2]);

    }

    free(weights);

    return result;
}