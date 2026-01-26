# 1. CMakeの最小バージョンを指定
cmake_minimum_required(VERSION 3.10)

# 2. プロジェクト名と言語を指定
project(MatrixCalcTool LANGUAGES C)

# 3. コンパイルオプションの設定
# -Wall: 警告をすべて表示, -Wextra: さらに詳細な警告
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# 4. インクルードディレクトリ（ヘッダファイルの場所）を指定
include_directories(include)

# 5. ライブラリを定義
# ライブラリが増えたらここに追加していく
set(LIB_SOURCES
    src/matrix.c
)
add_library(matrix_core ${LIB_SOURCES})

# 6. アプリ本体の実行ファイルを作成
add_executable(matrix_tool src/main.c)
# アプリ本体で使用するライブラリリンク
target_link_libraries(matrix_tool matrix_core m)

# 7. テスト用実行ファイルを作成
set(TEST_SOURCES
    test/test_matrix.c
    test/test_main.c
)
add_executable(unittest ${TEST_SOURCES})
# テストで使用するライブラリのリンク
target_link_libraries(unittest matrix_core m)