#ifndef __export_box_hpp__
#define __export_box_hpp__

#include "Box.hpp"

void exportBox(py::module &m)
{
    py::class_<Box>(m, "Box")
        .def(py::init<Point2D&>())
        .def(py::init<>())

        .def_readwrite("L", &Box::L)
        .def_readwrite("Lmin", &Box::Lmin)
        .def_readwrite("Lmax", &Box::Lmax);
}

#endif