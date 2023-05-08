#ifndef __export_randomclass_hpp__
#define __export_randomclass_hpp__

#include <pybind11/pybind11.h>
#include "RandomClass.hpp"

void exportRandomClass(py::module &m)
{
    py::class_<RandomClass>(m, "RandomClass")
        //Here we export the constructor
        .def(py::init<unsigned int>())

        //this is how we expose the variables
        
        //this is how we expose the functions
        .def("rand", &RandomClass::rand)
        .def("randn", &RandomClass::randn)
        .def("randreal", &RandomClass::randreal)
        .def("randint", &RandomClass::randint)

        .def("getSeed", &RandomClass::getSeed)
        .def("setSeed", &RandomClass::setSeed);
}
#endif
