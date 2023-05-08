#include "Sigma12.hpp"

void Sigma12Force::compute(){

  this->updateForce();
  // std::cerr << _gradwca.size() << '\n';

  for (Particle& p : _sys.getParticles()){
    
    p.f.x = p.f.x + _gradwca[p.id].x;
    p.f.y = p.f.y + _gradwca[p.id].y;

  }
}

void Sigma12Force::updateForce(){

  _gradwca.clear();

  std::vector <double> u {0.0, 0.0, 0.0, 0.0};
  std::vector <Point2D> rn;
  
  for (Particle& p : _sys.getParticles()){

    // N, E, S, W vectors around particle p
    rn.clear();
    rn.push_back(p.r + Point2D(0.0, _dr * p.rad)); 
    rn.push_back(p.r + Point2D(_dr * p.rad, 0.0));
    rn.push_back(p.r - Point2D(_dr * p.rad, 0.0));
    rn.push_back(p.r - Point2D(0.0, _dr * p.rad));
    
    // calculate wca potential around current particle within 
    // u cutoff in final version
    for (const int& nbid : _sys.getNeighbors()[p.id]){

        // sum contributions only from particles other than current in outer loop
        if (p.id != nbid){

          for(int i = 0; i < 4; i++){
              u[i] += calculatePotential((_sys.getParticles()[nbid].r - rn[i]).magnitude());
          }
        }
    }
    
      // calculate gradwca for current particle
      _gradwca.push_back(Point2D((u[2] - u[1]) / (2 * _dr), 
                                 (u[3] - u[0]) / (2 * _dr)));
  }
}

double Sigma12Force::calculatePotential(double r) const {
  
  return _eps * std::pow(_sigma / r, 12);
}
