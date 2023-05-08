#ifndef __self_propulsion_force_hpp__
#define __self_propulsion_force_hpp__

#include "Force.hpp"

class SelfPropulsionForce : public Force{
  public:
    SelfPropulsionForce(System& sys, double alpha) : Force{sys, "SelfPropulsionForce", 0.0}, _alpha{alpha} {}
    ~SelfPropulsionForce() override = default;

    void compute() override;
    // double getRcut() const {return _rcut;}

  private:
      double _alpha;

};
#endif

