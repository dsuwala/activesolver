#ifndef __evolver_hpp__
#define __evolver_hpp__

#include "Force.hpp"
#include "SelfPropulsionForce.hpp"
#include "RandomClass.hpp"
#include "Torque.hpp"
#include "PolarAlignment.hpp"
#include "Integrator.hpp"
#include "ActiveMatterIntegrator.hpp"
#include "ChemActiveIntegrator.hpp"
#include "WCA.hpp"
#include "Sigma12.hpp"

#include <string>
#include <map>
#include <cmath>
#include <iostream>

class Evolver{

  public: 
    //Evolver(System& sys, double dt) : _system{sys}, _dt{dt}, _noise{6.28} {}
    //Evolver(System& sys, double dt, double noise) : _system{sys}, _dt{dt}, _noise{noise} {}
    explicit Evolver(System& sys) : _system{sys}{}
    //_noise initializeb by roughly 2PI --> workaround?
    //void addForce(const std::string name, std::unique_ptr<Force> f){_forces[name] = std::move(f);}

    void addForce(const std::string name, std::map<std::string, double>& pars);
    void addTorque(const std::string name, std::map<std::string, double>& pars);
    void addIntegrator(const std::string name, std::map<std::string, double>& pars);

    void computeForces();
    void evolve();
    void updateNeighborList(double rcut);

    //double getNoise() const {return _noise;}

    void setGlobalRcut(const double rcut) {_rcutGlob = rcut;}
    void setTimeStep(const double dt) {_dt = dt;}
    double getTimeStep() const {return _dt;}
    
    //std::map <std::string, double>& getRcutList() {return _rcutList;}

    void integrate() const;
    void resetForcesTorquesEnergy();
    void resetForcesTorques();
    void resetEnergy();

    std::map<std::string, std::unique_ptr<Force>>& getForces(){return _forces;}
    std::map<std::string, std::unique_ptr<Torque>>& getTorques(){return _torques;}
    std::map<std::string, std::shared_ptr<Integrator>>& getIntegrators(){return _integrators;}

  private: 
    // "dictionary" of all used force pointers associated with their names
    System& _system;
    double _dt;
    double _rcutGlob; //global rcut

    std::map<std::string, std::unique_ptr<Force>> _forces;
    std::map<std::string, std::unique_ptr<Torque>> _torques;

    std::map<std::string, std::shared_ptr<Integrator>> _integrators;
    //double _D = 1.0; // direction alignment noise const. NOT USED currently
    //double _noise; // noise range [-noise/2., noise/2.]

};


#endif
