#include "csv_reader.h"
#include "markowitz.h"
#include "optimal.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <csv_file_path>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    int num_simulations = atoi(argv[2]);

    CSVData *csv_data = read_csv(filepath);

    // 计算收益率
    double **returns = calculate_returns(csv_data->data, csv_data->rows, csv_data->cols);

    // 计算平均收益率
    double *mean_returns = calculate_mean_returns(returns, csv_data->rows, csv_data->cols);
    
    // 计算波动率
    // double *volatility = calculate_volatility(returns, csv_data->rows, csv_data->cols);

    // 计算协方差矩阵
    double **cov_matrix = calculate_covariance_matrix(returns, csv_data->rows, csv_data->cols);

    // j计算组合年化收益
    // double ann_ret = portfolio_annulised_return(weights, mean_returns, csv_data->cols);

    // 计算组合年化波动率
    // double ann_std = portfolio_annulised_std(weights, cov_matrix, csv_data->cols);

    // 进行Markowitz优化
    // double *weights = markowitz_optimize(cov_matrix, returns, csv_data->cols);

    // 基于Monte Carlo 的Markowitz优化
    double **result = monte_carlo(num_simulations, mean_returns, cov_matrix, csv_data->cols);

    // 输出结果
    for (int i = 0; i < num_simulations; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%f, ", result[i][j]);
        }
        printf("\n");
    }

    // printf("Mean Returns:\n");
    // for (int i = 0; i < csv_data->cols; i++) {
    //     printf("%s: %f\n", csv_data->colnames[i + 1], mean_returns[i]);
    // }

    // printf("\nVolatility:\n");
    // for (int i = 0; i < csv_data->cols; i++) {
    //     printf("%s: %.6f\n", csv_data->colnames[i + 1], volatility[i]);
    // }

    // printf("\nCovariance Matrix:\n");
    // for (int i = 0; i < csv_data->cols; i++) {
    //     for (int j = 0; j < csv_data->cols; j++) {
    //         printf("%f ", cov_matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("\nPortfolio Weights:\n");
    // for (int i = 0; i < csv_data->cols; i++) {
    //     printf("  %s: %f\n", csv_data->colnames[i + 1], weights[i]);
    // }

    // printf("\nPortfolio Annulized Performace:\n  Return: %f\n  Volatility: %f\n", ann_ret, ann_std);

    // 释放内存
    free(mean_returns);
    // free(volatility);
    for (int i = 0; i < csv_data->cols; i++) {
        free(cov_matrix[i]);
    }
    for (int i = 0; i < csv_data->rows - 1; i++) {
        free(returns[i]);
    }
    free(cov_matrix);
    free(returns);
    // free(weights);
    free_csv_data(csv_data);

    for (int i = 0; i < num_simulations; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}
