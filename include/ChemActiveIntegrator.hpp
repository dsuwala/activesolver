#ifndef __chem_active_integrator_hpp__
#define __chem_active_integrator_hpp__

#include "Integrator.hpp"
#include "RandomClass.hpp"
#include <memory>
#include <map>
#include <cmath>

class ChemActiveIntegrator : public Integrator{

  public:
    ChemActiveIntegrator(System& sys, std::map<std::string, double> params, double dt) : Integrator{sys, "ChemActiveIntegrator", dt, params["hasNoise"]}, 
      _dzetaPos{params["dzetaPos"]}, _dzetaRot{params["dzetaRot"]}, 
      _Gpos{params["gammaPos"]}, _Grot{params["gammaRot"]}, 
      _Dc {params["Dc"]}, _k{params["k"]}, _c0{params["c0"]}, 
      _dr{params["dr"]}, _pe{params["pe"]}, _delta{params["delta"]}{
        
        _random = std::make_unique<RandomClass> (12312312);
      }

    ~ChemActiveIntegrator() override = default;

    void integrate() override;
    
    // fill _c matrix calculatin c3d for each point given by 
    // provided discretization number
    void updateChemicalField();
    void calculateConcentrationGrad(Particle& sample, Particle& drain, std::vector<double> c);
    
  private:
    
    //rotational and positional drag coefficients
    double _Gpos;
    double _Grot;

    // rotational and positional chemical field gradient coefficient
    double _dzetaRot;
    double _dzetaPos;
    
    // chemical concentration
    double _Dc; //diffusion. Have to be much larger than particles diffusion
    double _k;
    double _pi = 3.14159265359;
    double _c0; //assumes uniform concentration at the beginning
    std::vector <Point2D> _gradc; // gradient c for each particle
    int _cUpdateN;                // update chemical field every steps
    double _delta;                // screening lenght parameter

    // distance from the particle boundary to calculate 
    // gradient. Used in calculations as _dr * particle radius
    double _dr;                    

    // peclet number
    double _pe;

    std::unique_ptr<RandomClass> _random;



};

#endif
