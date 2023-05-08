#ifndef __export_system_hpp__
#define __export_system_hpp__

#include "System.hpp"
#include "Particle.hpp"
#include "System.hpp"

void exportSystem(py::module &m)
{
    py::class_<System>(m, "System")
        .def(py::init<Box&>())

        .def("getBox", &System::getBox)
        .def("addParticle", &System::addParticle)
        .def("getParticles", &System::getParticles)
        .def("getNeighbors", &System::getNeighbors)
        .def("getSize", &System::getSize);
}

#endif
