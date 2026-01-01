# 1. CMakeの最小バージョンを指定（3.10以上が一般的）
cmake_minimum_required(VERSION 3.10)

# 2. プロジェクト名と言語を指定
project(MatrixCalcTool LANGUAGES C)

# 3. コンパイルオプションの設定
# -Wall: 警告をすべて表示, -Wextra: さらに詳細な警告
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# 4. インクルードディレクトリ（ヘッダファイルの場所）を指定
include_directories(include)

# 5. ソースファイルのリストを定義
# ファイルが増えたらここに追加していく
set(SOURCES
    src/main.c
)

# 6. 実行ファイルの生成設定
# 実行ファイル名 "matrix_tool" を SOURCES から作成
add_executable(matrix_tool ${SOURCES})

# 7. 数学ライブラリ (math.h / -lm) のリンク
# Linux環境で sqrt などを使うために必要
target_link_libraries(matrix_tool m)