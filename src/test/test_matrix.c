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
    Matrix *result = create_matrix(2, 2);

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

    for (size_t i = 0; i < rows * cols; i++)
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
assert(add_matrix(NULL, NULL) == NULL);
int status = print_matrix(NULL);
assert(status == 1);
printf("TE-SUB-03: PASS\n");
}
