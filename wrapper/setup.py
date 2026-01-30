import os
import sys
from setuptools import setup, Extension

BASE_DIR = "/home/kazu/git/C_tools"
WRAPPER_DIR = os.path.join(BASE_DIR, "wrapper")
INC_DIR = os.path.join(BASE_DIR, "include")
SRC_DIR = os.path.join(BASE_DIR, "src")
# 成果物（バイナリ）の出力先をルート直下のbuildに絶対パスで固定
ABS_BUILD_DIR = os.path.join(BASE_DIR, "build")

if sys.platform == 'win32':
    compile_args = ['/Ox']
else:
    compile_args = ['-O3', '-fPIC']

setup(
    name="MTools",
    version="1.0.1",
    author="K",
    license="MIT License",
    ext_modules=[
        Extension(
            "MTools",
            sources=[
                os.path.join(WRAPPER_DIR, "mtools_wrapper.c"),
                os.path.join(SRC_DIR, "matrix.c")
            ],
            include_dirs=[INC_DIR, WRAPPER_DIR],
            extra_compile_args=compile_args,
        )
    ],
    options={
        "build_ext": {
            "build_lib": ABS_BUILD_DIR,  # ここでルートのbuildを指定
            "build_temp": os.path.join(ABS_BUILD_DIR, "temp")
        }
    }
)