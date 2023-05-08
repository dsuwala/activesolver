#ifndef __wca_force_hpp__
#define __wca_force_hpp__

#include "Force.hpp"

class WCAforce: public Force{
  public:
    WCAforce(System& sys, double epsilon, double sigma, double dr, double rcut) : Force{sys, "WCA", rcut}, 
    _eps{epsilon}, _sigma{sigma}, _dr{dr} {}
    ~WCAforce() override = default;

    void compute() override;

    void updateForce(); //recalculate wca potential gradient
    // double getRcut() const {return _rcut;}
    double calculateWCA(double r); // calculate wca potential for a given r

  private:
      double _eps; // strenght
      double _sigma; //particle diameter
      std::vector <Point2D> _gradwca; //vector of forces exerted for 
      // each particle to be used in compute method
      double _dr; //resolution for gradient calculation

};
#endif

