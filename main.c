#include "csv_reader.h"
#include "markowitz.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <csv_file_path>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    CSVData *csv_data = read_csv(filepath);

    // 计算收益率
    double **returns = calculate_returns(csv_data->data, csv_data->rows, csv_data->cols);

    // 计算平均收益率
    double *mean_returns = calculate_returns(returns, csv_data->rows, csv_data->cols);
    
    // 计算波动率
    // double *volatility = calculate_volatility(returns, csv_data->rows, csv_data->cols);

    // 计算组合年化波动率
    // double std = portfolio_annulised_std(float *weights, double **cov_matrix, int cols);

    // 计算协方差矩阵
    double **cov_matrix = calculate_covariance_matrix(returns, csv_data->rows, csv_data->cols);

    // 进行Markowitz优化
    double *weights = markowitz_optimize(cov_matrix, returns, csv_data->cols);

    // 输出结果
    printf("Mean Returns:\n");
    for (int i = 0; i < csv_data->cols; i++) {
        printf("%s: %.6f\n", csv_data->colnames[i + 1], mean_returns[i]);
    }

    printf("\n Annulized Volatility:\n");
    for (int i = 0; i < csv_data->cols; i++) {
        printf("%s: %.6f\n", csv_data->colnames[i + 1], volatility[i]);
    }

    printf("\nCovariance Matrix:\n");
    for (int i = 0; i < csv_data->cols; i++) {
        for (int j = 0; j < csv_data->cols; j++) {
            printf("%.4f ", cov_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nPortfolio Weights:\n");
    for (int i = 0; i < csv_data->cols; i++) {
        printf("%s: %.4f\n", csv_data->colnames[i + 1], weights[i]);
    }

    // 释放内存
    free(returns);
    free(volatility);
    for (int i = 0; i < csv_data->cols; i++) {
        free(cov_matrix[i]);
    }
    free(cov_matrix);
    free(weights);
    free_csv_data(csv_data);

    return 0;
}
