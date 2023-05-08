#include "Evolver.hpp"

void Evolver::addForce(const std::string name, std::map<std::string, double>& pars){

  if (name.compare("SelfPropulsionForce") == 0){

    _forces[name] = std::make_unique<SelfPropulsionForce>(_system, pars["alpha"]);
    //_rcutList["SelfPropulsionForce"] = pars["rcut"];
  }else if (name.compare("WCA") == 0){

    _forces[name] = std::make_unique<WCAforce>(_system, pars["epsilon"], pars["sigma"], pars["dr"], pars["rcut"]);
  }else if (name.compare("Sigma12") == 0){

    _forces[name] = std::make_unique<Sigma12Force>(_system, pars["epsilon"], pars["sigma"], pars["dr"], pars["rcut"]);
  }else{

    std::cerr << "Force not found" << '\n';
  }

}

void Evolver::addTorque(const std::string name, std::map<std::string, double>& pars){

  if (name.compare("PolarAlignment") == 0){

    _torques[name] = std::make_unique<PolarAlignment>(_system, pars["rcut"], pars["k"]);
    //_rcutList["PolarAlignment"] = pars["rcut"];
  }else{

    std::cerr << "Torque not found" << '\n';
  }

}

void Evolver::addIntegrator(const std::string name, std::map<std::string, double>& pars){
  
  if(name.compare("ActiveMatterIntegrator") == 0){
    _integrators[name] = std::make_shared<ActiveMatterIntegrator>(_system, pars, _dt);
    
  }else if(name.compare("ChemActiveIntegrator") == 0){
    _integrators[name] = std::make_shared<ChemActiveIntegrator>(_system, pars, _dt);
    
  }
  else{
    std::cerr << "Integrator not found" << '\n';
  }
}

void Evolver::resetForcesTorquesEnergy(){

  for(Particle& p : _system.getParticles()){
      p.f.x = 0.0;
      p.f.y = 0.0;
      p.t = 0;
      p.e = 0;
      p.n = Point2D(std::cos(p.theta), std::sin(p.theta));
  }
}

void Evolver::resetForcesTorques(){

  for(Particle& p : _system.getParticles()){
      p.f.x = 0.0;
      p.f.y = 0.0;
      p.t = 0;
  }
}

void Evolver::resetEnergy(){

  // std::cerr << "WARNING: support for energy calculation not implemented yet" << '\n';
  for(Particle& p : _system.getParticles()){
      p.e = 0;
  }
}


void Evolver::computeForces(){
  
  // std::cerr << "evolver compute forces called" << '\n';

  for (const auto& force : _forces){
    
    if (force.second->getRcut() != _rcutGlob && force.second->getRcut() != 0.0){

      this->updateNeighborList(force.second->getRcut());
    }
      force.second->compute();

  }

  for (const auto& torque : _torques){

    if (torque.second->getRcut() != _rcutGlob && torque.second->getRcut() != 0.0){

      this->updateNeighborList(torque.second->getRcut());
    }

    torque.second->compute();
  }

}

void Evolver::updateNeighborList(double rcut){
  // std::cerr << "neighbor list constructed" << '\n';

  _system.initializeCellList(rcut);

  _system.fillCellList();

  _system.calculateNeighborList(rcut);
  
}

void Evolver::evolve(){
  
  this->resetForcesTorquesEnergy();
  
  this->updateNeighborList(_rcutGlob);
  
  // std::cerr << "Evolver: neighbors of 0: ";
  // for (const int& id : _system.getNeighbors()[0]) std::cerr << id;
  // std::cerr << '\n';

  this->computeForces();

  this->integrate(); 
  
  _system.applyPeriodic();
  // _system.applyHardWall();

}

void Evolver::integrate() const{ 

  for (auto const& integrator : _integrators){
    integrator.second->integrate(); 
  }

}
