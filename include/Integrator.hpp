#ifndef __integrator_hpp__
#define __integrator_hpp__

#include "System.hpp"
#include <string>

class Integrator{

  public:

    Integrator(System& sys, std::string const& name, double& dt, bool hasNoise) : _system{sys}, _name{name}, _dt{dt}, _hasNoise{hasNoise} {}
    virtual ~Integrator() = default;
    virtual void integrate() = 0; //contains equation of motion to evolve by one time-step

    std::string getName() const {return _name;}


  protected:
    System& _system;
    std::string _name;
    double _dt;
    bool _hasNoise;

};

#endif
