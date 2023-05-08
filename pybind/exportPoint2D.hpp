#ifndef __export_point2d_hpp__
#define __export_point2d_hpp__

#include "Point2D.hpp"

void exportPoint2D(py::module &m)
{
    py::class_<Point2D>(m, "Point2D")
        //Here we export the constructor
        .def(py::init<double, double>())
        .def(py::init<>())
        //this is how we expose the variables
        // .def_readwrite("x", &Point2D::x)
        // .def_readwrite("y", &Point2D::y)
        
        .def("__add__", &Point2D::operator+)
        .def("__sub__", &Point2D::operator-)
        //.def("__mul__", &Point2D::operator*)
        
        // // defines < operator
        .def("__lt__", &Point2D::operator<)

        // // defines > operator
        .def("__gt__", &Point2D::operator>)
        .def("norm", &Point2D::magnitude)

        //.def("__idiv__", &Point2D::operator/=)
        //.def("__imul__", &Point2D::operator*=)

        //this is how we expose the functions
        .def_readwrite("x", &Point2D::x)
        .def_readwrite("y", &Point2D::y);

}

void exportPoint2Dvector(py::module &m)
{
    py::class_<std::vector<Point2D>>(m, "Point2DList")
        .def(py::init<>())
        .def("clear", &std::vector<Point2D>::clear)
        .def("pop_back", &std::vector<Point2D>::pop_back)
        .def("append", (void (std::vector<Point2D>::*)(const Point2D &)) & std::vector<Point2D>::push_back)
        .def("__len__", [](const std::vector<Point2D> &v) { return v.size(); })
        .def(
            "__iter__", [](std::vector<Point2D> &v) { return py::make_iterator(v.begin(), v.end()); }, py::keep_alive<0, 1>())
        .def("__getitem__", [](const std::vector<Point2D> &v, size_t i) { if (i >= v.size()) throw py::index_error(); return v[i]; })
        .def("__setitem__", [](std::vector<Point2D> &v, size_t i, Point2D &d) { if (i >= v.size()) throw py::index_error(); v[i] = d; });
}

void exportPoint2DvectorVector(py::module &m)
{
    py::class_<std::vector<std::vector<Point2D>>>(m, "std::vector<Point2D>ListofLists")
        .def(py::init<>())
        .def("clear", &std::vector<std::vector<Point2D>>::clear)
        .def("pop_back", &std::vector<std::vector<Point2D>>::pop_back)
        .def("append", (void (std::vector<std::vector<Point2D>>::*)(const std::vector<Point2D> &)) & std::vector<std::vector<Point2D>>::push_back)
        .def("__len__", [](const std::vector<std::vector<Point2D>> &v) { return v.size(); })
        .def(
            "__iter__", [](std::vector<std::vector<Point2D>> &v) { return py::make_iterator(v.begin(), v.end()); }, py::keep_alive<0, 1>())
        .def("__getitem__", [](const std::vector<std::vector<Point2D>> &v, size_t i) { if (i >= v.size()) throw py::index_error(); return v[i]; })
        .def("__setitem__", [](std::vector<std::vector<Point2D>> &v, size_t i, std::vector<Point2D> &d) { if (i >= v.size()) throw py::index_error(); v[i] = d; });
}

#endif
