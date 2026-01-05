#ifndef MATRIX_H
#define MATRIX_H

typedef struct { 
    int rows; 
    int cols;
     float *data;
 } Matrix;

Matrix *create_matrix(int rows, int cols);
int print_matrix(Matrix *data);
Matrix *add_matrix(Matrix *data_x, Matrix *data_y);
void free_matrix(Matrix *data);

#endif