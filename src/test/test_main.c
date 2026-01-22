#include <stdio.h>
#include "math.h"
#include "matrix.h"

extern void test_tn01();
extern void test_tn02();
extern void test_tn03();
extern void test_tn04();
extern void test_te01();
extern void test_te02();
extern void test_te03_te04();
extern void test_te05();

extern void test_sub_tn01();
extern void test_sub_te02();
extern void test_sub_te03();

extern void test_hadamard_products_tn01();
extern void test_hadamard_products_te01();
extern void test_hadamard_products_te02();

extern void test_dot_products_tn01();
extern void test_dot_products_te01();
extern void test_dot_products_te02();
int main(void){
    printf("--- Starting Unit Tests ---\n");
    test_tn01();
    test_tn02();
    test_tn03();
    test_tn04();
    test_te01();
    test_te02();
    test_te03_te04();
    test_te05();

    test_sub_tn01();
    test_sub_te02();
    test_sub_te03();

    test_hadamard_products_tn01();
    test_hadamard_products_te01();
    test_hadamard_products_te02();

    test_dot_products_tn01();
    test_dot_products_te01();
    test_dot_products_te02();
    printf("All tests passed!\n");
    return 0;
}