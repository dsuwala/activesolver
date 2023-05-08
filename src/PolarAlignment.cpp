#include "PolarAlignment.hpp"

#include <iostream>

double PolarAlignment::getTorque(Particle& p){

    double neighborTheta = 0.0;


    for (int id : _sys.getNeighbors()[p.id]){

        neighborTheta += std::sin(_sys.getParticles()[id].theta - p.theta);

        //double deg2rad = 3.14159265359 / 180.;
    }

    return  (_k / (_pi * _rcut)) * neighborTheta;
}

void PolarAlignment::compute(){

    for (auto& p : _sys.getParticles()){
        p.t += getTorque(p);
    }

}
