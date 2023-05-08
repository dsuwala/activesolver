#ifndef __polar_alignment_hpp__
#define __polar_alignment_hpp__

#include "Torque.hpp"
#include <cmath>

class PolarAlignment : public Torque{
  public:
    PolarAlignment(System& sys, double R, double k) : Torque{sys, "PolarAlignment", R}, _k{k} {}
    ~PolarAlignment() override = default;

    void compute() override;

    double getTorque(Particle& p);
    // double getRcut() const {return _R;};

  private:
      // double _R; //neighbor radius
      double _k;
      const double _pi = 3.14159265358979323846;

};
#endif

