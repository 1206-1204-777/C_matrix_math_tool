#ifndef MATRIX_H
#define MATRIX_H

typedef struct { 
    size_t rows; 
    size_t cols;
    double *data;
 } Matrix;

Matrix *create_matrix(size_t rows, size_t cols);
int print_matrix(const Matrix *data);
Matrix *add_matrix(const Matrix *data_x, const Matrix *data_y);
Matrix *sub_matrix(const Matrix *data_x, const Matrix *data_y);
Matrix *hadamard_product(const Matrix *data_x, const Matrix *data_y);
Matrix *dot_product(const Matrix *data_x, const Matrix *data_y);
Matrix *div_matrix(const Matrix *data_x, const Matrix *data_y);
void free_matrix(Matrix *data);

#endif