from distutils.core import setup, Extension

cpp_args = ['-std=c++11', '-stdlib=libc++']

ext_modules = [
    Extension(
        'alpha_shape',
        ['alpha_shape.cpp'],
        include_dirs=['/Users/scottberry/.virtualenvs/pybind11/include/site/python2.7'],
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
    ext_modules=ext_modules,
)
