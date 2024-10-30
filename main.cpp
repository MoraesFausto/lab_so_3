#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct {
    int row;
    int col;
    double **matrix;
    double *row_mean;
    double *col_geom_mean;
} MatrixData;

void *calculate_row_mean(void *arg) {
    MatrixData *data = (MatrixData *)arg;
    int row = data->row;
    int col = data->col;
    double **matrix = data->matrix;

    for (int i = 0; i < row; i++) {
        double sum = 0.0;
        for (int j = 0; j < col; j++) {
            sum += matrix[i][j];
        }
        data->row_mean[i] = sum / col;
    }
    pthread_exit(NULL);
}

void *calculate_col_geom_mean(void *arg) {
    MatrixData *data = (MatrixData *)arg;
    int row = data->row;
    int col = data->col;
    double **matrix = data->matrix;

    for (int j = 0; j < col; j++) {
        double product = 1.0;
        for (int i = 0; i < row; i++) {
            product *= matrix[i][j];
        }
        data->col_geom_mean[j] = pow(product, 1.0 / row);
    }
    pthread_exit(NULL);
}

void generate_matrix_file(int row, int col, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d %d\n", row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fprintf(file, "%d ", rand() % 100 + 1);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void read_matrix_file(const char *filename, double ***matrix, int *row, int *col) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", row, col);
    *matrix = (double **)malloc((*row) * sizeof(double *));
    for (int i = 0; i < *row; i++) {
        (*matrix)[i] = (double *)malloc((*col) * sizeof(double));
        for (int j = 0; j < *col; j++) {
            fscanf(file, "%lf", &(*matrix)[i][j]);
        }
    }
    fclose(file);
}

void write_results_to_file(const char *filename, double *row_mean, int row, double *col_geom_mean, int col) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open result file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Row Means:\n");
    for (int i = 0; i < row; i++) {
        fprintf(file, "Row %d: %.2f\n", i + 1, row_mean[i]);
    }

    fprintf(file, "\nColumn Geometric Means:\n");
    for (int j = 0; j < col; j++) {
        fprintf(file, "Column %d: %.2f\n", j + 1, col_geom_mean[j]);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <M> <N> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    const char *output_file = argv[3];

    srand(time(NULL));
    generate_matrix_file(row, col, "matrix.txt");

    double **matrix;
    read_matrix_file("matrix.txt", &matrix, &row, &col);

    double *row_mean = (double *)malloc(row * sizeof(double));
    double *col_geom_mean = (double *)malloc(col * sizeof(double));

    MatrixData data = {row, col, matrix, row_mean, col_geom_mean};

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, calculate_row_mean, &data);
    pthread_create(&thread2, NULL, calculate_col_geom_mean, &data);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    write_results_to_file(output_file, row_mean, row, col_geom_mean, col);

    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(row_mean);
    free(col_geom_mean);

    return EXIT_SUCCESS;
}
