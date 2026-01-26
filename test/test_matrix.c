#include <stdio.h>
#include "matrix.h"
#include <assert.h>
#include <stdint.h>

void test_tn01(){
    size_t rows = 2, cols = 2;
    Matrix *result = create_matrix(rows, cols);
   
        assert(result->rows == rows);
        assert(result->cols == cols);
        assert(result->data != NULL);
        for (size_t i = 0; i < rows * cols; i++)
        {
            assert(result->data[i] == 0.0);
            
        }
        free_matrix(result);
        printf("TN-01: PASS\n");


}
void test_tn02(){
    size_t rows = 2, cols = 2;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(rows, cols);

    for (size_t i = 0; i < rows * cols; i++)
    {
        mat_a->data[i] = 2.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = add_matrix(mat_a, mat_b);

    assert(result != NULL);
    for (size_t i = 0; i < rows * cols; i++)
    {
        assert(result->data[i] == 4.0);
    }
    

        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TN-02: PASS\n");


}
void test_tn03(){
    size_t rows = 2, cols = 2;
    Matrix *result = create_matrix(rows, cols);

        int status = print_matrix(result);
        assert(status == 0);
        free_matrix(result);
        printf("TN-03: PASS\n");


}

void test_tn04(){
    size_t rows = 2, cols = 2;
    Matrix *result = create_matrix(rows, cols);
        free_matrix(result);
        printf("TN-04: PASS\n");
}

void test_te01(){
    size_t rows = 0, cols = 5;
    Matrix *result = create_matrix(rows, cols);
    assert(result == NULL);
    free_matrix(result);
    printf("TE-01: PASS\n");


}
void test_te02(){
    size_t rows = 2, cols = 3;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(3, cols);

    for (size_t i = 0; i < rows * cols; i++)
    {
        mat_a->data[i] = 2.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = add_matrix(mat_a, mat_b);

    assert(result == NULL);
        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TE-02: PASS\n");


}
void test_te03_te04(){
assert(add_matrix(NULL, NULL) == NULL);
int status = print_matrix(NULL);
assert(status == 1);
printf("TE-03: PASS\n");
printf("TE-04: PASS\n");
}

void test_te05(){
assert(create_matrix(SIZE_MAX, SIZE_MAX) == NULL);

printf("TE-05: PASS\n");
}

void test_sub_tn01(){
    size_t rows = 6, cols = 2;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(rows, cols);

    for (size_t i = 0; i < rows * cols; i++)
    {
        mat_a->data[i] = 6.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = sub_matrix(mat_a, mat_b);

    assert(result != NULL);
    for (size_t i = 0; i < rows * cols; i++)
    {
        assert(result->data[i] == 4.0);
    }
    

        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TN-SUB-01: PASS\n");

}

void test_sub_te02(){
    size_t rows = 2, cols = 3;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(3, cols);

    for (size_t i = 0; i < mat_a->rows * mat_b->cols; i++)
    {
        mat_a->data[i] = 2.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = sub_matrix(mat_a, mat_b);

    assert(result == NULL);
        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TE-SUB-02: PASS\n");


}

void test_sub_te03(){
assert(sub_matrix(NULL, NULL) == NULL);
int status = print_matrix(NULL);
assert(status == 1);
printf("TE-SUB-03: PASS\n");
}

void test_hadamard_products_tn01(){
    size_t rows = 6, cols = 2;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(rows, cols);

    for (size_t i = 0; i < rows * cols; i++)
    {
        mat_a->data[i] = 6.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = hadamard_product(mat_a, mat_b);

    assert(result != NULL);
    for (size_t i = 0; i < rows * cols; i++)
    {
        assert(result->data[i] == 12.0);
    }
    

        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TN-HADAMARD_PRODUCT-01: PASS\n");

}

void test_hadamard_products_te01(){
    size_t rows = 2, cols = 3;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(3, cols);

    for (size_t i = 0; i < mat_a->rows * mat_b->cols; i++)
    {
        mat_a->data[i] = 2.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = hadamard_product(mat_a, mat_b);

    assert(result == NULL);
        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TE-HADAMARD_PRODUCT-01: PASS\n");


}

void test_hadamard_products_te02(){
assert(hadamard_product(NULL, NULL) == NULL);
int status = print_matrix(NULL);
assert(status == 1);
printf("TE-HADAMARD_PRODUCT-02: PASS\n");
}

void test_dot_products_tn01(){
   size_t row = 2;
    size_t col = 3;


    Matrix *data_x = create_matrix(row, col);
    Matrix *data_y = create_matrix(3, 2);

    for (size_t i = 0; i < row * col; i++)
    {
        data_x->data[i] = 8.0;
        data_y->data[i] = 5.0;
    }
    Matrix *result = dot_product(data_x, data_y);
    assert(result != NULL);
    for (size_t i = 0; i < result->rows * result->cols; i++)
    {
        assert(result->data[i] == 120.0);
    }
    

        free_matrix(data_x);
        free_matrix(data_y);
        free_matrix(result);
        printf("TN-DOT_PRODUCT-01: PASS\n");


}
void test_dot_products_te01(){
    size_t rows = 2, cols = 3;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(rows, cols);

    for (size_t i = 0; i < mat_a->rows * mat_b->cols; i++)
    {
        mat_a->data[i] = 2.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = dot_product(mat_a, mat_b);

    assert(result == NULL);
        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TE-DOT_PRODUCT-01: PASS\n");


}
void test_dot_products_te02(){
assert(dot_product(NULL, NULL) == NULL);
int status = print_matrix(NULL);
assert(status == 1);
printf("TE-DOT_PRODUCT-02: PASS\n");
}

void test_div_matrix_tn01(){
    size_t rows = 6, cols = 2;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(rows, cols);

    for (size_t i = 0; i < rows * cols; i++)
    {
        mat_a->data[i] = 6.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = div_matrix(mat_a, mat_b);

    assert(result != NULL);
    for (size_t i = 0; i < rows * cols; i++)
    {
        assert(result->data[i] == 3.0);
    }
    

        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TN-DIV_MATRIX-01: PASS\n");

}

void test_div_matrix_te01(){
    size_t rows = 2, cols = 3;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(3, cols);

    for (size_t i = 0; i < mat_a->rows * mat_b->cols; i++)
    {
        mat_a->data[i] = 2.0;
        mat_b->data[i] = 2.0;
    }
    Matrix *result = div_matrix(mat_a, mat_b);

    assert(result == NULL);
        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TE-DIV_MATRIX-01: PASS\n");


}

void test_div_matrix_te02(){
assert(div_matrix(NULL, NULL) == NULL);
int status = print_matrix(NULL);
assert(status == 1);
printf("TE-DIV_MATRIX-02: PASS\n");
}

void test_div_matrix_te03(){
    size_t rows = 2, cols = 3;
    Matrix *mat_a = create_matrix(rows, cols);
    Matrix *mat_b = create_matrix(rows, cols);

    for (size_t i = 0; i < mat_a->rows * mat_b->cols; i++)
    {
        mat_a->data[i] = 2.0;
        mat_b->data[i] = 0.0;
    }
    Matrix *result = div_matrix(mat_a, mat_b);

    assert(result == NULL);
        free_matrix(mat_a);
        free_matrix(mat_b);
        free_matrix(result);
        printf("TE-DIV_MATRIX-03: PASS\n");


}
