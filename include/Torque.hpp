#ifndef __torque_hpp__
#define __torque_hpp__

#include "System.hpp"
#include <string>
#include <memory>

class Torque{

    public: 
      Torque(System& sys, std::string name, double rcut) : _sys{sys}, _name{name}, _rcut{rcut} {}
      virtual ~Torque() = default;
      virtual void compute() = 0;

      std::string getName() const { return _name; }
      double getRcut() const {return _rcut;}

    protected:
      System& _sys;
      std::string _name;
      double _rcut;

};
#endif
