#include <gtest/gtest.h>
#include "Particle.hpp"
#include "Point2D.hpp"
#include "Box.hpp"
#include "System.hpp"
#include "SelfPropulsionForce.hpp"
#include "Evolver.hpp"
#include "Force.hpp"

#include <vector>
#include <iostream>
#include <string>

TEST(basicTests, setterTestPoint2D){
    Point2D p(2.0, 3.0);

    EXPECT_EQ(2.0, p.x);
    EXPECT_EQ(3.0, p.y);

    p.setX(4.0);
    EXPECT_EQ(4.0, p.x);
}

TEST(basicTests, magnitudePoint2D){
    Point2D p(-2.0, 3.0);
    
    EXPECT_EQ(sqrt(4.0 + 9.0), p.magnitude());
}

TEST(basicTests, point2DdiffMagnitude){
    Point2D p(-2.0, 3.0);
    Point2D q(-1.0, 4.0);
    Point2D r = p - q;
    
    EXPECT_EQ(-1.0, r.x);
    EXPECT_EQ(-1.0, r.y);
    EXPECT_EQ(sqrt(2), r.magnitude());
}

TEST(basicTests, particleConstructor){

    int type = 0;
    Point2D v0(0.23, 0.0);
    Point2D rr(1.37, 1.98);
    double th = 20.0;
    double rad = 1.0;
    Particle particle(type, rr, th, v0, rad);

    EXPECT_EQ(0, particle.type);
    EXPECT_EQ(20.0, particle.theta);
    EXPECT_EQ(0.23, particle.v.x);
    EXPECT_EQ(1.37, particle.r.x);
    EXPECT_EQ(1.98, particle.r.y);
}

TEST(basicTests, boxConstructor){
    Point2D size(3.0, 3.0);
    Box boxx(size);
    
    EXPECT_EQ(-1.5, boxx.Lmin.x);
    EXPECT_TRUE(-boxx.Lmin.x == boxx.Lmax.x);
    EXPECT_TRUE(-boxx.Lmin.y == boxx.Lmax.y);
}

TEST(basicTests, systemConstructor){

    int type = 0;
    Point2D v0(0.23, 0.0);
    Point2D rr(1.37, 1.98);
    double th = 20.0;
    double rad = 1.0;
    Particle particle(type, rr, th, v0, rad);

    Point2D size(3.0, 3.0);
    Box boxx(size);
    
    System system(boxx);
    system.addParticle(particle);
    
    EXPECT_EQ(1, system.getSize());
    EXPECT_EQ(20.0, system.getParticles().at(0).theta);
    EXPECT_EQ(0, system.getParticles().at(0).type);
    EXPECT_EQ(-1.5, system.getBox().Lmin.x);

    EXPECT_EQ(1.37, system.getParticles().at(0).r.x);
    EXPECT_EQ(1.98, system.getParticles().at(0).r.y);

}

TEST(basicTests, systemAddParticlesWorks){
    int type = 0;
    Point2D v0(0.23, 0.0);
    Point2D rr(0.0, 0.0);
    double th = 20.0;
    double rad = 1.0;
    Particle particle(type, rr, th, v0, rad);

    Point2D size(3.0, 3.0);
    Box boxx(size);
    
    System system(boxx);
    system.addParticle(particle);
    system.addParticle(particle);
    

    EXPECT_EQ(20.0, system.getParticles().at(0).theta);
    EXPECT_EQ(0, system.getParticles().at(0).type);
    EXPECT_EQ(-1.5, system.getBox().Lmin.x);
    EXPECT_EQ(0, system.getParticles().at(0).id);

    EXPECT_EQ(20.0, system.getParticles().at(1).theta);
    EXPECT_EQ(0, system.getParticles().at(1).type);
    EXPECT_EQ(-1.5, system.getBox().Lmin.x);
    EXPECT_EQ(1, system.getParticles().at(1).id);

    EXPECT_EQ(2, system.getSize());
}

TEST(basicTests, applyPeriodic){
    int type = 0;
    Point2D v0(0.23, 0.0);
    Point2D rr(0.00, 0.00);
    double th = 20.0;
    double rad = 1.0;
    Particle particle(type, rr, th, v0, rad);


    Point2D size(6.0, 6.0);
    Box boxx(size);
    
    System system(boxx);
    system.addParticle(particle);
    Point2D p(4.0, 4.0);

    system.getParticles().at(0).r = system.getParticles().at(0).r + p;
    system.applyPeriodic();
    
    EXPECT_EQ(-2.0, system.getParticles().at(0).r.x);
}


//TEST(basicTests, evolverConstructorWorks){
//
//    int type = 0;
//    Point2D v0(0.23, 0.0);
//    Point2D rr(0.0, 0.0);
//    double th = 20.0;
//    Particle particle(type, rr, th, v0);
//
//    Point2D size(3.0, 3.0);
//    Box boxx(size);
//    
//    System system(boxx);
//    system.addParticle(particle);
//    system.addParticle(particle);
//
//    double dt = 0.1;
//    Evolver evolver(system, dt);
//
//    EXPECT_EQ(0.1, evolver.getdt());
//
//}

TEST(basicTests, evolverAddForceWorks){

   int type = 0;
   Point2D v0(0.23, 0.0);
   Point2D rr(0.0, 0.0);
   double th = 20.0;
   double rad = 1.0;
   Particle particle(type, rr, th, v0, rad);

   Point2D size(3.0, 3.0);
   Box boxx(size);
   
   System system(boxx);
   system.addParticle(particle);
   system.addParticle(particle);

   //std::unique_ptr <Force> spf = std::make_unique<SelfPropulsionForce> (system, 2.0);
   //Evolver evolver; 
   //evolver.addForce("selfPropulsion", std::move(spf));

   std::map<std::string, double> parameters = {{"alpha", 2.0}};

   double dt = 2.0;
   Evolver evolver(system);
   evolver.setTimeStep(dt);

   evolver.addForce("SelfPropulsionForce", parameters);

   EXPECT_EQ("SelfPropulsionForce", evolver.getForces()["SelfPropulsionForce"]->getName());

}

TEST(basicTests, evolverAddTorqueWorks){

   int type = 0;
   Point2D v0(0.23, 0.0);
   Point2D rr(0.0, 0.0);
   double th = 20.0;
   double rad = 1.0;
   Particle particle(type, rr, th, v0, rad);

   Point2D size(3.0, 3.0);
   Box boxx(size);
   
   System system(boxx);
   system.addParticle(particle);
   system.addParticle(particle);

   std::map<std::string, double> parameters = {{"R", 2.0}, {"k", 1.2}};

   double dt = 2.0;
   Evolver evolver(system);
   evolver.setTimeStep(dt);

   evolver.addTorque("PolarAlignment", parameters);

   EXPECT_EQ("PolarAlignment", evolver.getTorques()["PolarAlignment"]->getName());

}


TEST(basicTests, evolverAddIntegratorWorks){

   int type = 0;
   Point2D v0(0.23, 0.0);
   Point2D rr(0.0, 0.0);
   double th = 20.0;
   double rad = 1.0;
   Particle particle(type, rr, th, v0, rad);

   Point2D size(3.0, 3.0);
   Box boxx(size);
   
   System system(boxx);
   system.addParticle(particle);
   system.addParticle(particle);

   std::map<std::string, double> parameters = {{"Dpos", 2.0}, {"Drot", 1.2}, {"gammaPos", 1.2}, {"gammaRot", 1.2}, {"hasNoise", false}};

   double dt = 2.0;
   Evolver evolver(system);
   evolver.setTimeStep(dt);

   evolver.addIntegrator("ActiveMatterIntegrator", parameters);

   EXPECT_EQ("ActiveMatterIntegrator", evolver.getIntegrators()["ActiveMatterIntegrator"]->getName());

}

TEST(basicTests, evolverAddChemActiveIntegratorWorks){

   int type = 0;
   Point2D v0(0.23, 0.0);
   Point2D rr(0.0, 0.0);
   double th = 20.0;
   double rad = 1.0;
   Particle particle(type, rr, th, v0, rad);

   Point2D size(3.0, 3.0);
   Box boxx(size);
   
   System system(boxx);
   system.addParticle(particle);
   system.addParticle(particle);

//    std::map<std::string, double> parameters = {{"Dpos", 2.0}, {"Drot", 1.2}, {"gammaPos", 1.2}, {"gammaRot", 1.2}};
   std::map<std::string, double> parameters = {{"dzetaPos", 15.4}, {"dzetaRot", -0.38}, 
                                                     {"gammaPos", 1.0}, {"gammaRot", 1.0},
                                                     {"Dc"      , 4.0}, {"k"       , 0.5}, {"c0", 2.0},
                                                     {"dr"      , 0.2}, {"pe"      , 8}, 
                                                     {"hasNoise", false}, {"delta" , 0.3}};

   double dt = 2.0;
   Evolver evolver(system);
   evolver.setTimeStep(dt);

   evolver.addIntegrator("ChemActiveIntegrator", parameters);

   EXPECT_EQ("ChemActiveIntegrator", evolver.getIntegrators()["ChemActiveIntegrator"]->getName());

}

TEST(basicTests, evolverAddWCAForceWorks){

   int type = 0;
   Point2D v0(0.23, 0.0);
   Point2D rr(0.0, 0.0);
   double th = 20.0;
   double rad = 1.0;
   Particle particle(type, rr, th, v0, rad);

   Point2D size(3.0, 3.0);
   Box boxx(size);
   
   System system(boxx);
   system.addParticle(particle);
   system.addParticle(particle);

   std::map<std::string, double> parameters = {{"epsilon", 2.0},
                                               {"sigma", 2.0},
                                               {"dr"   , 0.2},
                                               {"rcut", std::pow(2, 1. / 6.) * 2.0}};

   double dt = 2.0;
   Evolver evolver(system);
   evolver.setTimeStep(dt);

   evolver.addForce("WCA", parameters);

   EXPECT_EQ("WCA", evolver.getForces()["WCA"]->getName());

}

// TEST(basicTests, evolverWCAparametersOK){

//    int type = 0;
//    Point2D v0(0.23, 0.0);
//    Point2D rr(0.0, 0.0);
//    double th = 20.0;
//    Particle particle(type, rr, th, v0);

//    Point2D size(3.0, 3.0);
//    Box boxx(size);
   
//    System system(boxx);
//    system.addParticle(particle);
//    system.addParticle(particle);

//    std::map<std::string, double> parameters = {{"epsilon", 2.0},
//                                                {"sigma", 2.0},
//                                                {"dr"   , 0.2},
//                                                {"rcut", std::pow(2, 1. / 6.) * 2.0}};

//    double dt = 2.0;
//    Evolver evolver(system);
//    evolver.setTimeStep(dt);

//    evolver.addForce("WCA", parameters);

//    EXPECT_EQ("WCA", evolver.getForces()["WCA"]->getName());

// }