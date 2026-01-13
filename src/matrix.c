#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "matrix.h"

Matrix *create_matrix(size_t rows, size_t cols){
    if (rows <=0 || cols <= 0){
        fprintf(stderr,"引数で値が渡されませんでした。\n");
        return NULL;

    }

    if (rows > 0 && cols > (SIZE_MAX / sizeof(double))/ rows){
        fprintf(stderr,"メモリの最大値を超えています。\n");
        return NULL;
    }
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    if (m == NULL)
    {
       fprintf(stderr,"メモリ確保に失敗しました。\n");
       return NULL;
    }

    m->data = NULL;
    m->rows = rows;
    m->cols = cols;

    m->data = (double *)calloc(rows * cols, sizeof(double));
    if (m->data == NULL)
    {
        fprintf(stderr,"メモリ確保に失敗しました。\n");
        free_matrix(m);
        return NULL;
    }


    return m;
};


int print_matrix(const Matrix *data){
    if (data == NULL)
    {
        fprintf(stderr,"引数でポインタが渡されませんでした。\n");
        return 1;
    }
    for (size_t i = 0; i < data->rows; i++)
    {
       for (size_t j = 0; j < data->cols; j++)
       {
        printf("%f\n", data->data[i * data->cols + j]);

       }
       
    }
    
    return 0;
};

Matrix *add_matrix(const Matrix *data_x, const Matrix *data_y){
    if (data_x == NULL || data_y == NULL)
    {
        fprintf(stderr,"引数でポインタが渡されませんでした。\n;");
        return NULL;
    }
    if (data_x->rows != data_y->rows || data_x->cols != data_y->cols)
    {
        fprintf(stderr,"行列の形状が一致しませんでした。\n");
        return NULL;
    }
    Matrix *y = create_matrix(data_x->rows, data_x->cols);
    if (y == NULL) return NULL;
    for (size_t i = 0; i < data_x->rows; i++)
    {
        for (size_t j = 0; j < data_x->cols; j++)
        {
            y->data[i * y->cols + j] = data_x->data[i * data_x->cols + j] + data_y->data[i * data_y->cols + j];
        }
        
    }
    return y;

};

Matrix *sub_matrix(const Matrix *data_x, const Matrix *data_y){
    if (data_x == NULL || data_y == NULL)
    {
        fprintf(stderr,"引数でポインタが渡されませんでした。\n;");
        return NULL;
    }
    if (data_x->rows != data_y->rows || data_x->cols != data_y->cols)
    {
        fprintf(stderr,"行列の形状が一致しませんでした。\n");
        return NULL;
    }
    Matrix *y = create_matrix(data_x->rows, data_x->cols);
    if (y == NULL) return NULL;
    for (size_t i = 0; i < data_x->rows; i++)
    {
        for (size_t j = 0; j < data_x->cols; j++)
        {
            y->data[i * y->cols + j] = data_x->data[i * data_x->cols + j] - data_y->data[i * data_y->cols + j];
        }
        
    }
    return y;

}

void free_matrix(Matrix *data){
    if (data == NULL)
    {
        fprintf(stderr,"引数でポインタが渡されませんでした。\n");
        return;
    }
    free(data->data);
    free(data);
};
