import ctypes
from ctypes import POINTER, c_double, c_size_t, Structure

# 構造体の定義
class Matrix(Structure):
    _fields_ = [
        ("rows", c_size_t),
        ("cols", c_size_t),
        ("data", POINTER(c_double))
    ]

lib = ctypes.CDLL("./build/libmatrix.so")

lib.create_matrix.argtypes = [c_size_t, c_size_t]
lib.create_matrix.restype = POINTER(Matrix)

lib.print_matrix.argtypes = [POINTER(Matrix)]
lib.print_matrix.restype = None

lib.add_matrix.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.add_matrix.restype = POINTER(Matrix)

lib.sub_matrix.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.sub_matrix.restype = POINTER(Matrix)

lib.hadamard_product.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.hadamard_product.restype = POINTER(Matrix)

lib.dot_product.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.dot_product.restype = POINTER(Matrix)

lib.div_matrix.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.div_matrix.restype = POINTER(Matrix)

lib.free_matrix.argtypes = [POINTER(Matrix)]
lib.free_matrix.restype = None

lib.print_matrix.argtypes = [POINTER(Matrix)]
lib.print_matrix.restype = ctypes.c_int