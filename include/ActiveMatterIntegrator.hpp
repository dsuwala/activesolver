#ifndef __active_matter_integrator_hpp__
#define __active_matter_integrator_hpp__

#include "Integrator.hpp"
#include "RandomClass.hpp"
#include <memory>
#include <map>

class ActiveMatterIntegrator : public Integrator{

  public:
    ActiveMatterIntegrator(System& sys, std::map<std::string, double> params, double dt) : Integrator{sys, "ActiveMatterIntegrator", dt, params["hasNoise"]}, 
      _Dpos{params["Dpos"]}, _Drot{params["Drot"]}, _Gpos{params["gammaPos"]}, _Grot{params["gammaRot"]} {
        
        _random = std::make_unique<RandomClass> (12312312);
      }

    ~ActiveMatterIntegrator() override = default;

    void integrate() override;

  private:
    
    //positional and rotational diffusion coefficients
    double _Dpos; 
    double _Drot;

    //rotational and positional drag coefficients
    double _Gpos;
    double _Grot;
    std::unique_ptr<RandomClass> _random;



};

#endif
