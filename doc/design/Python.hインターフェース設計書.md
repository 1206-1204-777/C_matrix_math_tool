# `Python.h` インターフェース設計書
## 1. 設計の目的

1. **ブリッジ機能**: Pythonの `MTools.Matrix` オブジェクトとC言語の `Matrix` 構造体 を橋渡しする。
2. **自動メモリ管理**: Pythonのガベージコレクションに連動させ、`free_matrix` を自動実行する。
3. **演算子オーバーロード**: `+` 演算子で C の `add_matrix` を呼び出せるようにする。
4. **演算子オーバーロード**: `-` 演算子で C の `sub_matrix` を呼び出せるようにする。
5. **演算子オーバーロード**: `*` 演算子で C の `hadamard_product` を呼び出せるようにする。
6. **演算子オーバーロード**: `/` 演算子で C の `div_matrix` を呼び出せるようにする。

---

## 2. 主要構成要素

| 要素 | 設計内容 | 備考 |
| --- | --- | --- |
| **Header Include** | `#include <Python.h>` および `#include "matrix.h"` | コアロジックとの分離を徹底 |
| **Object Structure** | `typedef struct { PyObject_HEAD Matrix* m_ptr; } MatrixObject;` | Cのポインタを内部に隠蔽 |
| **Wrapper Function** | `Matrix_init`, `Matrix_dealloc`, `Matrix_truediv`  | ライフサイクルと演算の定義 |
| **Method Table** | `Matrix_methods[]` 配列 | `print_matrix` などを登録 |
| **Number Methods** | `PyNumberMethods` 構造体 | `/` などの演算子をC関数に紐付け |
| **Type Definition** | `PyTypeObject MatrixType` | クラス「Matrix」の設計図 |

---

## 3. インターフェース構造（実装詳細）

### 3.1. 構造体とライフサイクル

* **`Matrix_init` (初期化)**:
* `PyArg_ParseTuple(args, "kk", &rows, &cols)` でサイズを取得。
* 内部で `create_matrix(rows, cols)` を呼び出し、`m_ptr` に格納。


* **`Matrix_dealloc` (解放)**:
* `if (self->m_ptr) free_matrix(self->m_ptr);` を実行。
* 利用者が `del` を意識せずともメモリが解放される仕組み。



### 3.2. 演算子ラッパー

* **`Matrix_trueadd` (加算 `+`)**:
* 引数 `a`, `b` を `MatrixObject` にキャスト。
* `add_matrix(a->m_ptr, b->m_ptr)` を実行。
* 結果が `NULL` なら `PyErr_SetString(PyExc_ZeroDivisionError, "...")` を発行。
* 成功時は新しい `MatrixObject` を生成して返す。

* **`Matrix_truesub` (減算 `-`)**:
* 引数 `a`, `b` を `MatrixObject` にキャスト。
* `sub_matrix(a->m_ptr, b->m_ptr)` を実行。
* 結果が `NULL` なら `PyErr_SetString(PyExc_ZeroDivisionError, "...")` を発行。
* 成功時は新しい `MatrixObject` を生成して返す。

* **`Matrix_truemul` (乗算 `*`)**:
* 引数 `a`, `b` を `MatrixObject` にキャスト。
* `hadamard_product(a->m_ptr, b->m_ptr)` を実行。
* 結果が `NULL` なら `PyErr_SetString(PyExc_ZeroDivisionError, "...")` を発行。
* 成功時は新しい `MatrixObject` を生成して返す。

* **`Matrix_truediv` (除算 `/`)**:
* 引数 `a`, `b` を `MatrixObject` にキャスト。
* `div_matrix(a->m_ptr, b->m_ptr)` を実行。
* 結果が `NULL` なら `PyErr_SetString(PyExc_ZeroDivisionError, "...")` を発行。
* 成功時は新しい `MatrixObject` を生成して返す。



### 3.3. メソッドテーブル（公開関数）

```c
static PyMethodDef Matrix_methods[] = {
    {"print_matrix", (PyCFunction)Matrix_print, METH_NOARGS, "行列を表示"},
    {"set_data", (PyCFunction)Matrix_set_data, METH_VARARGS, "リストからデータを注入"},
    {NULL, NULL, 0, NULL}
};

```

### 3.4. 演算子スロット

```c
static PyNumberMethods Matrix_as_number = {
    .nb_true_add = (binaryfunc)Matrix_trueadd,
    .nb_true_sub = (binaryfunc)Matrix_truesub,
    .nb_true_mul = (binaryfunc)Matrix_truemul,
    .nb_true_div = (binaryfunc)Matrix_truediv,
}

```
### 3.5. 演算データの注入方法
- 補助関数`Matrix_set_data`を定義
    - プロトタイプ: `PyObject *Matrix_set_data(PyObject *self, PyObject *args)`

#### 処理フロー

1. **引数の解析**: `PyArg_ParseTuple` を使用し、Python側から渡された単一の引数を `PyObject*`（リスト）として取得する
2. **型チェック**: `PyList_Check` を呼び出し、渡されたオブジェクトが Python のリスト型であるか確認する
    * リストでない場合は `TypeError` を設定し、`NULL` を返却する

3. **サイズの検証**: `PyList_Size` で取得したリストの長さが、内部構造体 `m_ptr` の `rows * cols` と一致するか判定する
    * 不一致の場合は `ValueError` を設定し、`NULL` を返却する

4. **データの変換ループ**:
    * リストの要素数分だけループを回し、`PyList_GetItem` で Python の数値オブジェクトを 1 つずつ取り出す
        * 取り出したオブジェクトを `PyFloat_AsDouble` を用いて C 言語の `double` 型へ変換する
        * 変換された値を、C 側の実データ領域 `self->m_ptr->data[i]` に順次代入する

5. **エラーハンドリング**: ループ中、数値への変換に失敗した場合は、直ちにループを中断し `NULL` を返却して Python 側に例外を投げる
6. **完了処理**: 全てのデータ注入が正常に完了した場合、`Py_RETURN_NONE` を返却して Python 側に制御を戻す

---

## 4. 例外・エラー処理の設計

| 項目 | 処理内容 | 備考 |
| --- | --- | --- |
| **型チェック** | 引数が `Matrix` 型でない場合に `TypeError` を発行 | `PyObject_TypeCheck` を使用 |
| **形状不一致** | `add_matrix` が `NULL` を返した場合に例外発行 | `簡易版matlix_matrix_tool_設計書.md` に準拠 |
| **形状不一致** | `sub_matrix` が `NULL` を返した場合に例外発行 | `簡易版sub_matrix追加設計.md` に準拠 |
| **形状不一致** | `div_matrix` が `NULL` を返した場合に例外発行 | `簡易版div_matrix追加設計.md` に準拠 |
| **形状不一致** | `hadamard_product` が `NULL` を返した場合に例外発行 | `簡易版hadamard_product追加設計.md` に準拠 |
| **メモリ確保失敗** | `create_matrix` が `NULL` を返した場合に `PyErr_NoMemory()` | 安定性の確保 |

---