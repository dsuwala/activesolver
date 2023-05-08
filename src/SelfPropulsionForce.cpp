
#include "SelfPropulsionForce.hpp"

void SelfPropulsionForce::compute(){
  
  for (auto& particle : _sys.getParticles()){

    particle.f.x += particle.n.x * _alpha;
    particle.f.y += particle.n.y * _alpha;

  }
}
