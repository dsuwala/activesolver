#ifndef __sigma12_force_hpp
#define __sigma12_force_hpp

#include "Force.hpp"

class Sigma12Force: public Force{
  public:
    Sigma12Force(System& sys, double epsilon, double sigma, double dr, double rcut) : Force{sys, "Sigma12", rcut}, 
    _eps{epsilon}, _sigma{sigma}, _dr{dr} {}
    ~Sigma12Force() override = default;

    void compute() override;

    void updateForce(); //recalculate potential gradient
    // double getRcut() const {return _rcut;}
    double calculatePotential(double r) const; // calculate sigma 12 potential for a given r

  private:
      double _eps; // strength
      double _sigma; //particle diameter
      std::vector <Point2D> _gradwca; //vector of forces exerted for 
      // each particle to be used in compute method
      double _dr; //resolution for gradient calculation

};
#endif

