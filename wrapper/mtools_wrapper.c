#include <Python.h>
#include "matrix.h"

/* 1. オブジェクト定義 */
typedef struct {
    PyObject_HEAD
    Matrix *matrix; 
} MatrixObject;

PyTypeObject MatrixType;

/* 2. メモリ解放 */
static void Matrix_dealloc(MatrixObject *self) {
    if (self->matrix) {
        free_matrix(self->matrix);
    }
    Py_TYPE(self)->tp_free((PyObject *)self);
}

/* 3. 内部演算ロジック (演算子と関数で共有) */
static PyObject* _matrix_binop_logic(PyObject *v, PyObject *w, Matrix* (*core_func)(const Matrix*, const Matrix*)) {
    if (!PyObject_TypeCheck(v, &MatrixType) || !PyObject_TypeCheck(w, &MatrixType)) {
        Py_RETURN_NOTIMPLEMENTED;
    }
    Matrix *res_raw = core_func(((MatrixObject *)v)->matrix, ((MatrixObject *)w)->matrix);
    if (!res_raw) return NULL;

    MatrixObject *res_obj = (MatrixObject *)PyObject_New(MatrixObject, &MatrixType);
    res_obj->matrix = res_raw;
    return (PyObject *)res_obj;
}

/* 4. 各演算子の実装 */
static PyObject* Matrix_nb_add(PyObject *v, PyObject *w) { return _matrix_binop_logic(v, w, add_matrix); }
static PyObject* Matrix_nb_subtract(PyObject *v, PyObject *w) { return _matrix_binop_logic(v, w, sub_matrix); }
static PyObject* Matrix_nb_multiply(PyObject *v, PyObject *w) { return _matrix_binop_logic(v, w, hadamard_product); }
static PyObject* Matrix_nb_true_divide(PyObject *v, PyObject *w) { return _matrix_binop_logic(v, w, div_matrix); }
static PyObject* Matrix_nb_matrix_multiply(PyObject *v, PyObject *w) { return _matrix_binop_logic(v, w, dot_product); }

/* 5. モジュール関数用のラップ (mt.add(x, y) 等) */
static PyObject* MTools_func_wrap(PyObject *self, PyObject *args, PyObject* (*op_logic)(PyObject*, PyObject*)) {
    PyObject *v, *w;
    if (!PyArg_ParseTuple(args, "OO", &v, &w)) return NULL;
    return op_logic(v, w);
}

static PyObject* mt_f_add(PyObject *s, PyObject *a) { return MTools_func_wrap(s, a, Matrix_nb_add); }
static PyObject* mt_f_sub(PyObject *s, PyObject *a) { return MTools_func_wrap(s, a, Matrix_nb_subtract); }
static PyObject* mt_f_mul(PyObject *s, PyObject *a) { return MTools_func_wrap(s, a, Matrix_nb_multiply); }
static PyObject* mt_f_div(PyObject *s, PyObject *a) { return MTools_func_wrap(s, a, Matrix_nb_true_divide); }
static PyObject* mt_f_dot(PyObject *s, PyObject *a) { return MTools_func_wrap(s, a, Matrix_nb_matrix_multiply); }

/* 6. Matrixオブジェクトのメソッド (print, set_data) */
static PyObject* Matrix_print(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    print_matrix(((MatrixObject *)self)->matrix);
    Py_RETURN_NONE;
}

static PyObject* Matrix_set_data(PyObject *self, PyObject *args) {
    PyObject *data_list;
    if (!PyArg_ParseTuple(args, "O", &data_list)) return NULL;
    if (!PyList_Check(data_list)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a list.");
        return NULL;
    }
    Matrix *m = ((MatrixObject *)self)->matrix;
    Py_ssize_t n = PyList_Size(data_list);
    size_t total = m->rows * m->cols;
    for (Py_ssize_t i = 0; i < n && i < (Py_ssize_t)total; i++) {
        m->data[i] = PyFloat_AsDouble(PyList_GetItem(data_list, i));
    }
    Py_RETURN_NONE;
}

static PyMethodDef Matrix_methods[] = {
    {"print", (PyCFunction)Matrix_print, METH_NOARGS, NULL},
    {"set_data", (PyCFunction)Matrix_set_data, METH_VARARGS, NULL},
    {NULL}
};

/* 7. 数値演算スロットの完全登録 */
static PyNumberMethods Matrix_as_number = {
    .nb_add = (binaryfunc)Matrix_nb_add,
    .nb_subtract = (binaryfunc)Matrix_nb_subtract,
    .nb_multiply = (binaryfunc)Matrix_nb_multiply,      // *
    .nb_true_divide = (binaryfunc)Matrix_nb_true_divide,   // /
    .nb_matrix_multiply = (binaryfunc)Matrix_nb_matrix_multiply, // @
};

/* 8. 型定義 */
PyTypeObject MatrixType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "MTools.Matrix",
    .tp_basicsize = sizeof(MatrixObject),
    .tp_dealloc = (destructor)Matrix_dealloc,
    .tp_as_number = &Matrix_as_number,
    .tp_methods = Matrix_methods,
    .tp_flags = Py_TPFLAGS_DEFAULT,
};

/* 9. モジュール関数定義 */
static PyObject* MTools_create_matrix(PyObject *self, PyObject *args) {
    size_t r, c;
    if (!PyArg_ParseTuple(args, "nn", &r, &c)) return NULL;
    Matrix *m = create_matrix(r, c);
    if (!m) return NULL;
    MatrixObject *obj = (MatrixObject *)PyObject_New(MatrixObject, &MatrixType);
    obj->matrix = m;
    return (PyObject *)obj;
}

static PyMethodDef MTools_methods[] = {
    {"create_matrix", (PyCFunction)MTools_create_matrix, METH_VARARGS, NULL},
    {"add", mt_f_add, METH_VARARGS, NULL},
    {"sub", mt_f_sub, METH_VARARGS, NULL},
    {"mul", mt_f_mul, METH_VARARGS, NULL},
    {"div", mt_f_div, METH_VARARGS, NULL},
    {"dot", mt_f_dot, METH_VARARGS, NULL},
    {NULL}
};

static struct PyModuleDef mtoolsmodule = { PyModuleDef_HEAD_INIT, "MTools", NULL, -1, MTools_methods };

PyMODINIT_FUNC PyInit_MTools(void) {
    PyObject *m = PyModule_Create(&mtoolsmodule);
    if (PyType_Ready(&MatrixType) < 0) return NULL;
    return m;
}