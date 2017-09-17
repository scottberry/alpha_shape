from distutils.core import setup, Extension

cpp_args = ['-std=c++11']

ext_modules = [
    Extension(
        'alpha_shape',
        ['alpha_shape.cpp'],
        include_dirs=['/usr/local/include/python2.7'],
        libraries=['CGAL', 'gmp'],
        language='c++',
        extra_compile_args=cpp_args
    ),
]

setup(
    name='alpha_shape',
    version='0.0.1',
    author='Scott Berry',
    author_email='scottdberry@gmail.com',
    description='Wrapper for CGAL Alpha_shape_3',
    install_requires=[
        'pybind11>=2.2.1'
    ],
    ext_modules=ext_modules,
)
