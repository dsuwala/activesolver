# Numerical Solver 
This project contains a c++ library for integrating equations of motion specified in Integrator Class with pretty much any force implemented as a Force class. Code is exported via 
pybind for usage in python. This code was created as a part of Computational Active Matter class conducted by Dr Daniel Matoz at the Faculty of Physics of the University of Warsaw, 
Poland. Unit tests are my own idea to speed up troubleshooting and were not included in the course itself ;)
Code is quite general and I am currently getting back to it to prepare some demonstrations, so If you are interested stay tuned ;)

## dependencies
    - cmake >= 3.16
    - pybind11 >= 2.9.1
    - c++ 14 support

Althrough local pybind11 copy is included, support for it is yet to be done.

## how to compile it

It's a cmake project, so standard 
```
mkdir build && cd build 
cmake ..
cmake --build . -j <# of cores> or make -j <# of cores>
```
should suffice. Python library file `cppmodule.so` will appear in `build/pybind/cppmodule.so`. Later you can copy/move it to main project directory 
with file `main.py`.

This project contains also unit tests provided via google test framework. You can launch them through binary `build/test/myUnitTests` (require 
this project compilation before).

## how to use it
You can import this module in the same way as any python library:
```python
import activeSolver
```
when `activeSolver.so` file is in the same directory as your python script or in include directory recognized by your system.