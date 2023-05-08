#include "WCA.hpp"

void WCAforce::compute(){

  this->updateForce();
  // std::cerr << "repulsion detected" << '\n';
  // std::cerr << "wca eps: " << _eps << " wca sigma: " << _sigma << " wca dr: " << _dr << '\n';

  for (Particle& p : _sys.getParticles()){
    
    // std::cout << "id " << p.id << '\n';
    // std::cout << p.f.x << " " << p.f.y << '\n';
    // std::cout << _gradwca[p.id].x << " " << _gradwca[p.id].y << '\n';
    
    p.f.x += _gradwca[p.id].x;
    p.f.y += _gradwca[p.id].y;
    
    // for (Particle& par : _sys.getParticles()) std::cerr << par.id << "force " << par.f.x << " " << par.f.y << '\n';

  }
}

void WCAforce::updateForce(){

  _gradwca.clear();

  std::vector <double> u {0.0, 0.0, 0.0, 0.0};
  std::vector <Point2D> rn;
  Point2D n; 
  
  for (Particle& sample: _sys.getParticles()){

    // N, E, S, W vectors around particle p
    rn.clear();

    // rn.push_back(p.r + Point2D(0.0, _dr * p.rad)); 
    // rn.push_back(p.r + Point2D(_dr * p.rad, 0.0));
    // rn.push_back(p.r - Point2D(_dr * p.rad, 0.0));
    // rn.push_back(p.r - Point2D(0.0, _dr * p.rad));

    rn.push_back(Point2D(0.0, _dr)); 
    rn.push_back(Point2D(_dr, 0.0));
    rn.push_back(Point2D(_dr, 0.0) * -1.0);
    rn.push_back(Point2D(0.0, _dr) * -1.0);
    

    // calculate wca potential around current particle within 
    // u cutoff in final version
    // for (const int& nbid : _sys.getNeighbors()[p.id]){
      

    //   // sum contributions only from particles other than current in outer loop
    //   if (p.id != nbid){
    //     for(int i = 0; i < 4; i++) u[i] += calculateWCA((_sys.getParticles()[nbid].r - rn[i]).magnitude());

    //   }
    // }

    // for (Particle& source : _sys.getParticles()){
    for (const int& sourceid : _sys.getNeighbors()[sample.id]){

      // sum contributions only from particles other than current in outer loop
      // if (sample.id != source.id){
      if (sample.id != sourceid){

        Particle source = _sys.getParticles()[sourceid];
        n = (sample.r - source.r) / std::abs((sample.r - source.r).magnitude());
        for(int i = 0; i < 4; i++){

          // std::cerr << "======================================" << '\n';
          // std::cerr << "nx: " << n.x << " ny: " << n.y << '\n';
          // std::cerr << "sample: " << sample.id << " source: " << source.id << '\n';
          u[i] += calculateWCA((n * (sample.r - source.r).magnitude() - rn[i]).magnitude());
          // std::cerr << "u: " << i << " " << u[i] << " rnx " << rn[i].x << " rny " << rn[i].y << '\n';
          // std::cerr << "distance vector: x:" << (n * (p.r - pp.r).magnitude()).x << " y:" << (n * (p.r - pp.r).magnitude()).y << '\n';
          // std::cerr << "distance: " << (n * (sample.r - source.r).magnitude() - rn[i]).magnitude() << '\n';
          // std::cerr << "======================================" << '\n';
        }
        
        // calculate gradwca for current particle
        _gradwca.push_back(Point2D((u[1] - u[2]) / (2 * _dr), 
                                   (u[0] - u[3]) / (2 * _dr)));
        
        // populate grad vector with zeros when there is only ifself as neighbor
        }else if(_sys.getNeighbors()[sample.id].size() == 1){

          _gradwca.push_back(Point2D(0.0, 0.0));
        }

        

        // std::cerr << "gradwca: x:" << (u[1] - u[2]) / (2 * _dr) << " y: " << (u[0] - u[3]) / (2 * _dr) << '\n' << '\n';
        u = {0.0, 0.0, 0.0, 0.0};

    }

    
  }
}

double WCAforce::calculateWCA(double r) {
  
  return 4 * _eps * (std::pow(_sigma / r, 12) - std::pow(_sigma / r, 6)) + _eps;
}
