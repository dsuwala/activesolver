#include "ChemActiveIntegrator.hpp"

void ChemActiveIntegrator::integrate(){

  updateChemicalField();

  for (Particle& p : _system.getParticles()){ 
  
    if(_hasNoise){

      p.r.x += _dt * _pe - _dzetaPos * _gradc[p.id].x + _dt * p.f.x / _Gpos + sqrt(_dt) * _random->randn(0, 1);
      p.r.y += _dt * _pe - _dzetaPos * _gradc[p.id].y + _dt * p.f.y / _Gpos + sqrt(_dt) * _random->randn(0, 1);
      
      double thetagradc = Point2D(-std::sin(p.theta), std::cos(p.theta)) * _gradc[p.id];
      p.theta += _dt * _dzetaRot * thetagradc + _dt * sqrt(_dt) * _random->randn(0, 1);
    }else{
      
      p.r.x += _dt * _pe - _dzetaPos * _gradc[p.id].x;
      p.r.y += _dt * _pe - _dzetaPos * _gradc[p.id].y;
      
      double thetagradc = Point2D(-std::sin(p.theta), std::cos(p.theta)) * _gradc[p.id];
      p.theta += _dt * _dzetaRot * thetagradc;
    }
    
  }

}


void ChemActiveIntegrator::updateChemicalField(){

  _gradc.clear();
  std::vector <double> c {_c0, _c0, _c0, _c0};
  //
  // N, E, S, W vectors around particle p

  for (Particle& p : _system.getParticles()){


    for (Particle& pp : _system.getParticles()){
      calculateConcentrationGrad(p, pp, c);
    }
    // calculate gradc for current particle
    _gradc.push_back(Point2D((c[2] - c[1]) / (2 * _dr), 
                             (c[3] - c[0]) / (2 * _dr)));
    
  }
  
}

void ChemActiveIntegrator::calculateConcentrationGrad(Particle& sample, Particle& drain, std::vector<double> c){
  // calculates concentration taking into account all other particles influence
  // calculate all c around current particle
  //
  std::vector <Point2D> rn;
  rn.clear();
  rn.push_back(Point2D(0.0, _dr)); 
  rn.push_back(Point2D(_dr, 0.0));
  rn.push_back(Point2D(_dr, 0.0) * -1.0);
  rn.push_back(Point2D(0.0, _dr) * -1.0);
  double screening_lenght = 2 * sample.rad * (1 + _delta);

  for (int i = 0; i < 4; i++) {
    // c calculated almost at r=p.r, but shifted by rn vectors to 
    // get gradient
    if(_system.getNeighbors()[sample.id].size() < 6){
      
      c[i] -= (_k / (4 * _pi * _Dc)) / (sample.r - drain.r + rn[i] ).magnitude();
    }else{
      c[i] -= (_k / (4 * _pi * _Dc)) * std::exp(- ((drain.r - sample.r - rn[i] ).magnitude() - screening_lenght) / screening_lenght);
    }

    // c cannot go below 0.0
    if (c[i] <= 0.0) c[i] = 0;
  }
  
}
