#ifndef __export_evolver_hpp__
#define __export_evolver_hpp__

#include "Evolver.hpp"
#include "System.hpp"
#include "Particle.hpp"

void exportEvolver(py::module &m)
{
    py::class_<Evolver>(m, "Evolver")
        //.def(py::init<System&, double>())
        //.def(py::init<System&, double, double>())

        .def(py::init<System&>())

        .def("addForce", &Evolver::addForce)
        .def("addTorque", &Evolver::addTorque)
        .def("addIntegrator", &Evolver::addIntegrator)
        .def("evolve", &Evolver::evolve)
        //.def("computeForces", &Evolver::computeForces)
        //.def("getNoise", &Evolver::getNoise)
        .def("setGlobalRcut", &Evolver::setGlobalRcut)
        .def("getTimeStep", &Evolver::getTimeStep)
        .def("setTimeStep", &Evolver::setTimeStep);
}

#endif
