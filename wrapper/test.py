import matrix_tools_wrapper as mtw

def test_python_integration():
    print("--- Testing Python Integration ---")

    mat_a = mtw.lib.create_matrix(2, 3)
    mat_b = mtw.lib.create_matrix(3, 2)


    for i in range(2 * 3):
        mat_a.contents.data[i] = 8.0
    

    for i in range(3 * 2):
        mat_b.contents.data[i] = 5.0

    print("Matrix A (2x3):")
    mtw.lib.print_matrix(mat_a)
    print("Matrix B (3x2):")
    mtw.lib.print_matrix(mat_b)


    print("\nExecuting Dot Product (A * B)...")
    result = mtw.lib.dot_product(mat_a, mat_b)

    if result:
        print("Result Matrix (2x2):")
        mtw.lib.print_matrix(result)

        mtw.lib.free_matrix(result) 
    else:
        print("Error: Calculation failed.")


    print("\nExecuting Division by Zero Check...")
    zero_mat = mtw.lib.create_matrix(2, 3) 
    div_result = mtw.lib.div_matrix(mat_a, zero_mat)
    
    if div_result is None or not div_result:
        print("Success: Zero division correctly handled (returned NULL).")

    mtw.lib.free_matrix(mat_a)
    mtw.lib.free_matrix(mat_b)
    mtw.lib.free_matrix(zero_mat)

if __name__ == "__main__":
    test_python_integration()