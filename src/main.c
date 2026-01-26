#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
int main(void)
{

    printf("Hello world!\n");
    size_t row = 2;
    size_t col = 3;


    Matrix *data_x = create_matrix(row, col);
    Matrix *data_y = create_matrix(row, col);

    for (size_t i = 0; i < row * col; i++)
    {
        data_x->data[i] = 8.0;
        data_y->data[i] = 0.0;
    }
    
    Matrix *result = div_matrix(data_x, data_y);
    if (result == NULL)
    {
        fprintf(stderr, "計算結果が正しく格納されませんでした。\n");
        free_matrix(data_x);
        free_matrix(data_y);
        exit(1);
    }
    print_matrix(result);
    free_matrix(data_x);
    free_matrix(data_y);
    free_matrix(result);
    return 0;
}
