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

    // 计算协方差矩阵
    double **cov_matrix = calculate_covariance_matrix(returns, csv_data->rows, csv_data->cols);

    // 基于Monte Carlo 的Markowitz优化
    double **result = monte_carlo(num_simulations, mean_returns, cov_matrix, csv_data->cols);

    // show result
    // print title
    for (int i = 0; i < csv_data->cols; i++) {
        printf("%s, ", csv_data->colnames[i+1]);  // colname[0]: Date, colname[1:cols+1]: AAPL, AMZN, ...
    }
    printf("return, volatility, sharp ratio, \n");
    // print data
    for (int i = 0; i < num_simulations; i++) {
        for (int j = 0; j < csv_data->cols + NUM_COLS; j++) {
            printf("%f, ", result[i][j]);
        }
        printf("\n");
    }

    // 释放内存
    // *mean_returns
    free(mean_returns);
    // **cov_matrix
    for (int i = 0; i < csv_data->cols; i++) {
        free(cov_matrix[i]);
    }
    free(cov_matrix);
    // **returns
    for (int i = 0; i < csv_data->rows - 1; i++) {
        free(returns[i]);
    }
    free(returns);
    // CSVData
    free_csv_data(csv_data);

    // **result
    for (int i = 0; i < num_simulations; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}
