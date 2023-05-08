#include "ActiveMatterIntegrator.hpp"

void ActiveMatterIntegrator::integrate(){

  // from a reason I don't know when I put this instead of 
  // full equations inside if/else I am not recieving 
  // physically correct msd curve
  // double noiseX, noiseY, noiseAngle;

  // if (_hasNoise){
  //   noiseX = _random->randn(0, 1);
  //   noiseY = _random->randn(0, 1);
  //   noiseAngle = _random->randn(0, 1);
  // }else{
  //   noiseX = 0;
  //   noiseY = 0;
  //   noiseAngle = 0;
  // }

  for (Particle& p : _system.getParticles()){ 
  

    if (_hasNoise){
      p.r.x += (1./_Gpos) * p.f.x * _dt + sqrt(2 * _Dpos * _dt) * _random->randn(0,1);
      p.r.y += (1./_Gpos) * p.f.y * _dt + sqrt(2 * _Dpos * _dt) * _random->randn(0,1);
      
      p.theta += (1./_Grot) * p.t * _dt + sqrt(2 * _Drot * _dt) * _random->randn(0,1);
    }else{
      p.r.x += (1./_Gpos) * p.f.x * _dt;
      p.r.y += (1./_Gpos) * p.f.y * _dt;
      
      p.theta += (1./_Grot) * p.t * _dt;

    }
    
  }

}

