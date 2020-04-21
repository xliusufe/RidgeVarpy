from setuptools import setup, Extension, find_packages
import numpy

VERSION = '1.0'
extensions = Extension(name = 'ridgevar._RidgeVarpy',  # name of our extension module
                        sources = ['src/cfunct.c', 'src/_cfunct.c'],
                        include_dirs = ['src'],
                        language='c' 
                        )


setup(
    name='RidgeVarpy', # A name show on Pypi.
    version=VERSION, 
    packages = ['ridgevar'],
    ext_modules = [extensions],
    license='MIT',
    description='A Python package for estimation of error variance via ridge regression.',
    long_description=open('README.md').read(),
    install_requires=[],
    url='https://github.com/xliusufe/RidgeVarpy/',
    author='Xu Liu',
    author_email='liu.xu@sufe.edu.cn',
    maintainer="Xu Liu",
    maintainer_email='liu.xu@sufe.edu.cn',  
    include_dirs = [numpy.get_include()],
    python_requires='>=3.5'
)
