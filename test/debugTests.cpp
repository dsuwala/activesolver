#include <gtest/gtest.h>
#include "Particle.hpp"
#include "Point2D.hpp"
#include "Box.hpp"
#include "System.hpp"
#include "SelfPropulsionForce.hpp"
#include "Evolver.hpp"
#include "Force.hpp"
#include "RandomClass.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
 
TEST(numericsTests, wcaTwoSpheresOutsideCutoffWorks){

   // given
   int type = 0;
   int N = 12; //apporach pbc loop at 13876
   double dt = 0.01;
   double rcut = 2.25;
   double b = 25.0;
   double rad = 1.0;

   Point2D v0(0.0, 0.0);
   Point2D size(b + 10.0, b + 10.0);
   
   RandomClass random(12312412);

   std::vector<Particle> particlesList;

   for (int i = 0; i < N; i++){
      auto rr = Point2D(random.randreal(- b / 2.0, b / 2.0), random.randreal(- b / 2.0, b / 2.0));
      double theta = random.randreal(- M_PI, M_PI);

      particlesList.emplace_back(type, rr, theta, v0, rad); 
   }

   Box boxx(size);
   System system(boxx);

   for (Particle const& p : particlesList) system.addParticle(p);
   
   // when
   Evolver evolver(system);
   
   evolver.setTimeStep(dt);
   evolver.setGlobalRcut(rcut);
   
   std::map<std::string, double> selfProp = {{"alpha", 0.5}};
   std::map<std::string, double> activeIntegratorParams = {{"Dpos", 1.0}, {"Drot", 1.0}, {"gammaPos", 1.0}, {"gammaRot", 1.0}, {"hasNoise", true}};
   std::map<std::string, double> wcaParams = {{"epsilon", 2.0}, {"sigma", 2.0}, {"dr", 0.001}, {"rcut", 2.25}};
   
   evolver.addIntegrator("ActiveMatterIntegrator", activeIntegratorParams);
   evolver.addForce("WCA", wcaParams);
   evolver.addForce("SelfPropulsionForce", selfProp);
   

   // then
   EXPECT_EQ("WCA", evolver.getForces()["WCA"]->getName());
   EXPECT_EQ("SelfPropulsionForce", evolver.getForces()["SelfPropulsionForce"]->getName());
   EXPECT_EQ("ActiveMatterIntegrator", evolver.getIntegrators()["ActiveMatterIntegrator"]->getName());
   
   double posx = system.getParticles()[0].r.x;

   for (int step = 0; step <= 50000; step++){
      std::cerr << step << '\n';
      evolver.evolve();
   }
   // evolver.evolve();
   // evolver.evolve();
   EXPECT_TRUE(posx != system.getParticles()[0].r.x);
   
   
   // evolver.evolve();

}