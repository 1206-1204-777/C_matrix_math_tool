## 1. 追加概要
- `sub_matrix`関数を追加し行列に対する減算を行う機能を追加

## 2. 追加内容
### プロトタイプ
- [sub_matrix]: `Matrix *sub_matrix(const Matrix *data_x, const Matrix *data_y);`
    - **引数**:
        - `const Matrix *data_x`: 計算に使用する配列
        - `const Matrix *data_y`: 計算に使用する配列
    - **戻り値**:
        - 成功時：`return y;`
        - 失敗時：呼び出し元にNULLを返す(`retun NULL`)

    - **処理内容（アルゴリズム）**:
        1. 引数`data_x`と引数`data_y`がNULLでないか確認
            * NULLの場合呼び出し元に `NULL` を返す
        2. 引数`data_x`と引数`data_y`の形状が一致しているか確認
            * 一致していない場合は呼び出し元に `NULL` を返す
        3. `create_matrix`を使い計算結果を格納するための配列`y`を作成
        4. `y`がNULLではないかチェックを行う
            * NULLの場合は場合呼び出し元に `NULL` を返す
        5. 2重ループを使い、配列`data_x`と配列`data_y`で対応するインデックス同士を減算
            * 1層目のループでインデックス`i`を取り出す
            * 2層目のループでインデックス`j`を取り出し`(*data_x).data[i * (*data_x).cols + j]`と`(*data_y).data[i * (*data_y).cols + j]` を減算する
            * 行列計算完了後結果を配列`y`に格納する
            * ループを使い配列`(*y).data[i * (*y).cols + j]`に減算結果を順に格納する
        6. 戻り値として配列`y`を返す

    - **メモリ管理**:
    - 関数内で `malloc` を行い配列を確保。
    - 戻り値のメモリ解放責任は呼び出し側に帰属(`free_matrix`を使用し開放)

###

## 3. 追加理由
- 四則演算に対応するため追加

## 4. 影響範囲
- `matrix.c`に追加関数を記載する
- `main.c`で配列を作成し減算処理を実行する
