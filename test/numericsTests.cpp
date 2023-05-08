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
#include <algorithm>



//TEST(numericsTests, computeForcesWorksOnlyTorquesNOPBC){
//    // TO FIX: this terrible one by one creation of particle list
//    // I want to have DRY code here
//    Point2D pt1(-2.0, 2.0);
//    Point2D pt2(-1.0, 1.0);
//    Point2D pt3(1.0, 1.0);
//    Point2D pt4(-2.0, -1.0);
//    Point2D pt5(1.0, -1.0);
//    Point2D pt6(0.0, 0.0);
//
//    int type = 0;
//    Point2D v0(0.00, 0.0);
//    Point2D rr(0.0, 0.0);
//
//    double deg2rad = 3.14159265359 / 180.;
//    double th1 = 20.0 * deg2rad;
//    double th2 = 15.0 * deg2rad;
//    double th3 = -40.0 * deg2rad;
//    double th4 = 60.0 * deg2rad;
//    double th5 = -60.0 * deg2rad;
//    double th6 = -30.0 * deg2rad;
//
//    Particle p1(type, pt1, th1, v0);
//    Particle p2(type, pt2, th2, v0);
//    Particle p3(type, pt3, th3, v0);
//    Particle p4(type, pt4, th4, v0);
//    Particle p5(type, pt5, th5, v0);
//    Particle p6(type, pt6, th6, v0);
//
//    std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6};
//
//    Point2D size(6.0, 6.0);
//    Box boxx(size);
//    
//    System system(boxx);
//    double dt = 0.1;
//    double noise = 0.0;
//
//    for (auto& p : particlesList) system.addParticle(p);
//
//    std::map<std::string, double> vicsek = {{"R", 1.5}, {"k", 1.2}};
//    std::map<std::string, double> selfPropulsion = {{"alpha", 2.0}};
//
//    Evolver evolver(system, dt, noise);
//    //evolver.addForce("SelfPropulsionForce", selfPropulsion);
//    evolver.addTorque("PolarAlignment", vicsek);
//
//    EXPECT_EQ(0.0, system.getParticles().at(5).t);
//    
//    evolver.computeForces();
//
//    EXPECT_NEAR(0.005680, system.getParticles().at(5).t, 0.00001);
//
//}
//
//TEST(numericsTests, computeForcesWorksOnlyForces){
//    // TO FIX: this terrible one by one creation of particle list
//    // I want to have DRY code here
//    Point2D pt1(-2.0, 2.0);
//    Point2D pt2(-1.0, 1.0);
//    Point2D pt3(1.0, 1.0);
//    Point2D pt4(-2.0, -1.0);
//    Point2D pt5(1.0, -1.0);
//    Point2D pt6(0.0, 0.0);
//
//    int type = 0;
//    Point2D v0(0.00, 0.0);
//    Point2D rr(0.0, 0.0);
//
//    double deg2rad = 3.14159265359 / 180.;
//    double th1 = 20.0 * deg2rad;
//    double th2 = 15.0 * deg2rad;
//    double th3 = -40.0 * deg2rad;
//    double th4 = 60.0 * deg2rad;
//    double th5 = -60.0 * deg2rad;
//    double th6 = -30.0 * deg2rad;
//
//    Particle p1(type, pt1, th1, v0);
//    Particle p2(type, pt2, th2, v0);
//    Particle p3(type, pt3, th3, v0);
//    Particle p4(type, pt4, th4, v0);
//    Particle p5(type, pt5, th5, v0);
//    Particle p6(type, pt6, th6, v0);
//
//    std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6};
//
//    Point2D size(6.0, 6.0);
//    Box boxx(size);
//    
//    System system(boxx);
//    double dt = 0.1;
//    double noise = 0.0;
//
//    for (auto& p : particlesList) system.addParticle(p);
//
//    std::map<std::string, double> selfPropulsion = {{"alpha", 2.0}};
//
//    Evolver evolver(system, dt, noise);
//    evolver.addForce("SelfPropulsionForce", selfPropulsion);
//
//    EXPECT_EQ(0.0, system.getParticles().at(5).f.getX());
//    EXPECT_EQ(0.0, system.getParticles().at(5).f.getY());
//    
//    evolver.computeForces();
//
//    EXPECT_NEAR(2 * 0.8660254, system.getParticles().at(5).f.getX(), 0.00001);
//    EXPECT_NEAR(2 * (-0.5), system.getParticles().at(5).f.getY(), 0.00001);
//}
//
//TEST(numericsTests, computeForcesWorksOnlyTorquesPBC){
//    // TO FIX: this terrible one by one creation of particle list
//    // I want to have DRY code here
//    Point2D pt1(-2.0, 2.0);
//    Point2D pt2(-2.5, 1.0);
//    Point2D pt3(2.0, -2.0);
//    Point2D pt4(1.0, 1.0);
//
//    int type = 0;
//    Point2D v0(0.00, 0.0);
//
//    double deg2rad = 3.14159265359 / 180.;
//    double th1 = 20.0 * deg2rad;
//    double th2 = -40.0 * deg2rad;
//    double th3 = 15.0 * deg2rad;
//    double th4 = -359.0 * deg2rad;
//
//    Particle p1(type, pt1, th1, v0);
//    Particle p2(type, pt2, th2, v0);
//    Particle p3(type, pt3, th3, v0);
//    Particle p4(type, pt4, th4, v0);
//
//    std::vector <Particle> particlesList{p1, p2, p3, p4};
//
//    Point2D size(6.0, 6.0);
//    Box boxx(size);
//    
//    System system(boxx);
//    double dt = 0.1;
//    double noise = 0.0;
//
//    for (auto& p : particlesList) system.addParticle(p);
//
//    std::map<std::string, double> vicsek = {{"R", 2 * sqrt(2) + 0.1}, {"k", 1.2}};
//
//    Evolver evolver(system, dt, noise);
//    evolver.addTorque("PolarAlignment", vicsek);
//
//    EXPECT_EQ(0.0, system.getParticles().at(2).t);
//    EXPECT_EQ(0.0, system.getParticles().at(0).t);
//    
//    evolver.computeForces();
//
//    EXPECT_NEAR(0.00388202, system.getParticles().at(2).t, 0.00001);
//    EXPECT_NEAR(-0.042455, system.getParticles().at(0).t, 0.00001);
//}
//
//TEST(numericsTests, computeForcesNoForcesRespected){
//    //check if there are no acceleration when there is no force
//    
//    Point2D pt1(-2.0, 2.0);
//    Point2D pt2(-2.5, 1.0);
//    Point2D pt3(2.0, -2.0);
//    Point2D pt4(1.0, 1.0);
//
//    int type = 0;
//    Point2D v0(0.44, 0.27);
//
//    double deg2rad = 3.14159265359 / 180.;
//    double th1 = 20.0 * deg2rad;
//    double th2 = -40.0 * deg2rad;
//    double th3 = 15.0 * deg2rad;
//    double th4 = -359.0 * deg2rad;
//
//    Particle p1(type, pt1, th1, v0);
//    Particle p2(type, pt2, th2, v0);
//    Particle p3(type, pt3, th3, v0);
//    Particle p4(type, pt4, th4, v0);
//
//    std::vector <Particle> particlesList{p1, p2, p3, p4};
//
//    Point2D size(6.0, 6.0);
//    Box boxx(size);
//    
//    System system(boxx);
//    double dt = 0.1;
//    double noise = 0.0;
//
//    for (auto& p : particlesList) system.addParticle(p);
//
//    std::map<std::string, double> vicsek = {{"R", 2 * sqrt(2) + 0.1}};
//
//    Evolver evolver(system, dt, noise);
//
//    evolver.computeForces();
//
//    int steps = 100;
//    evolver.evolve(steps);
//
//    EXPECT_EQ(0.44, system.getParticles().at(2).v.getX());
//    EXPECT_EQ(0.27, system.getParticles().at(2).v.getY());
//}
//
//TEST(numericsTests, evolverFirstEvolutionStepWorksNONOISE){
//
//    Point2D pt1(-2.0, 2.0);
//    Point2D pt2(-2.5, 1.0);
//    Point2D pt3(2.0, -2.0);
//    Point2D pt4(1.0, 1.0);
//
//    int type = 0;
//    Point2D v0(0.44, 0.27);
//
//    double deg2rad = 3.14159265359 / 180.;
//    double th1 = 20.0 * deg2rad;
//    double th2 = -40.0 * deg2rad;
//    double th3 = 15.0 * deg2rad;
//    double th4 = -359.0 * deg2rad;
//
//    Particle p1(type, pt1, th1, v0);
//    Particle p2(type, pt2, th2, v0);
//    Particle p3(type, pt3, th3, v0);
//    Particle p4(type, pt4, th4, v0);
//
//    std::vector <Particle> particlesList{p1, p2, p3, p4};
//
//    Point2D size(6.0, 6.0);
//    Box boxx(size);
//    
//    System system(boxx);
//    double dt = 0.1;
//    double noise = 0.0;
//
//    for (auto& p : particlesList) system.addParticle(p);
//
//    std::map<std::string, double> vicsek = {{"R", 2 * sqrt(2) + 0.1}};
//    std::map<std::string, double> selfProp = {{"alpha", 0.1}};
//
//    Evolver evolver(system, dt, noise);
//    evolver.addForce("SelfPropulsionForce", selfProp);
//
//    evolver.computeForces();
//
//    evolver.evolve(1);
//
//    EXPECT_NEAR(-1.9555301, system.getParticles().at(0).r.getX(), 0.00001);
//    EXPECT_NEAR(2.02717101, system.getParticles().at(0).r.getY(), 0.00001);
//
//    EXPECT_NEAR(2.04448296, system.getParticles().at(2).r.getX(), 0.00001);
//    EXPECT_NEAR(-1.97287059, system.getParticles().at(2).r.getY(), 0.00001);
//
//    EXPECT_NEAR(0.3489917, system.getParticles().at(0).theta, 0.0002);
//    EXPECT_NEAR(0.2618061, system.getParticles().at(2).theta, 0.0002);
//}


TEST(numericsTests, cellListInitializedCorrectly){

   Point2D pt1(2.0, 2.0);
   Point2D pt2(1.8, 1.8);
   Point2D pt3(2.2, 2.2);

   Point2D pt4(0.0, 0.0);
   Point2D pt5(0.2, 0.2);
   Point2D pt6(2.0, -2.0);
   Point2D pt7(-2.0, -2.0);

   int type = 0;
   Point2D v0(0.44, 0.27);

   double deg2rad = 3.14159265359 / 180.;
   double th = 20.0 * deg2rad;
   double rad = 1.0;

   Particle p1(type, pt1, th, v0, rad);
   Particle p2(type, pt2, th, v0, rad);
   Particle p3(type, pt3, th, v0, rad);
   Particle p4(type, pt4, th, v0, rad);
   Particle p5(type, pt5, th, v0, rad);
   Particle p6(type, pt6, th, v0, rad);
   Particle p7(type, pt7, th, v0, rad);

   std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6, p7};

   Point2D size(6.0, 6.0);
   Box boxx(size);
   
   System system(boxx);
   double dt = 0.1;
   double noise = 0.0;

   for (Particle const& p : particlesList) system.addParticle(p);

   system.initializeCellList(2);
   
   EXPECT_EQ(9, system.getBuckets().size());

}


TEST(numericsTests, cellListFilledCorrectly){

   Point2D pt1(2.0, 2.0);
   Point2D pt2(1.8, 1.8);
   Point2D pt3(2.2, 2.2);

   Point2D pt4(0.0, 0.0);
   Point2D pt5(0.2, 0.2);
   Point2D pt6(2.0, -2.0);
   Point2D pt7(-2.0, -2.0);

   int type = 0;
   Point2D v0(0.44, 0.27);

   double deg2rad = 3.14159265359 / 180.;
   double th = 20.0 * deg2rad;

   double rad = 1.0;
   Particle p1(type, pt1, th, v0, rad);
   Particle p2(type, pt2, th, v0, rad);
   Particle p3(type, pt3, th, v0, rad);
   Particle p4(type, pt4, th, v0, rad);
   Particle p5(type, pt5, th, v0, rad);
   Particle p6(type, pt6, th, v0, rad);
   Particle p7(type, pt7, th, v0, rad);

   std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6, p7};

   Point2D size(6.0, 6.0);
   Box boxx(size);
   
   System system(boxx);

   for (Particle const& p : particlesList) system.addParticle(p);

   system.initializeCellList(2);
   system.fillCellList();

   EXPECT_EQ(3, system.getBuckets()[8].size());
   EXPECT_EQ(2, system.getBuckets()[4].size());

   //test if particles 1,2,3 are in cell (2,2) <=> 8 after flattening
   EXPECT_EQ(0, system.getBuckets()[8][0]);
   EXPECT_EQ(1, system.getBuckets()[8][1]);
   EXPECT_EQ(2, system.getBuckets()[8][2]);

   EXPECT_EQ(5, system.getBuckets()[2][0]);
   EXPECT_EQ(6, system.getBuckets()[0][0]);

}

TEST(numericsTests, neighborListCorrect){

   Point2D pt1(2.0, 2.0);
   Point2D pt2(1.8, 1.8);
   Point2D pt3(2.2, 2.2);

   Point2D pt4(0.0, 0.0);
   Point2D pt5(0.2, 0.2);
   Point2D pt6(2.0, -2.0);
   Point2D pt7(-2.0, -2.0);

   int type = 0;
   Point2D v0(0.44, 0.27);

   double deg2rad = 3.14159265359 / 180.;
   double th = 20.0 * deg2rad;

   double rad = 1.0;
   Particle p1(type, pt1, th, v0, rad);
   Particle p2(type, pt2, th, v0, rad);
   Particle p3(type, pt3, th, v0, rad);
   Particle p4(type, pt4, th, v0, rad);
   Particle p5(type, pt5, th, v0, rad);
   Particle p6(type, pt6, th, v0, rad);
   Particle p7(type, pt7, th, v0, rad);

   std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6, p7};

   Point2D size(6.0, 6.0);
   Box boxx(size);
   
   System system(boxx);

   for (Particle const& p : particlesList) system.addParticle(p);

   system.initializeCellList(2.0);
   system.fillCellList();
   system.calculateNeighborList(2.0);
   
   std::vector <std::vector<int>> neighbors = system.getNeighbors();
   
   std::sort(neighbors[0].begin(), neighbors[0].end());

   std::vector <int> reference {0, 1, 2, 5};

   EXPECT_TRUE(neighbors[0] == reference);

}

TEST(numericsTests, evolutionOccurs){

   Point2D pt1(2.0, 2.0);
   Point2D pt2(1.8, 1.8);
   Point2D pt3(2.2, 2.2);

   Point2D pt4(0.0, 0.0);
   Point2D pt5(0.2, 0.2);
   Point2D pt6(2.0, -2.0);
   Point2D pt7(-2.0, -2.0);

   int type = 0;
   Point2D v0(0.44, 0.27);

   double deg2rad = 3.14159265359 / 180.;
   double th = 20.0 * deg2rad;

   double rad = 1.0;
   Particle p1(type, pt1, th, v0, rad);
   Particle p2(type, pt2, th, v0, rad);
   Particle p3(type, pt3, th, v0, rad);
   Particle p4(type, pt4, th, v0, rad);
   Particle p5(type, pt5, th, v0, rad);
   Particle p6(type, pt6, th, v0, rad);
   Particle p7(type, pt7, th, v0, rad);

   std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6, p7};

   Point2D size(6.0, 6.0);
   Box boxx(size);
   
   System system(boxx);

   for (Particle const& p : particlesList) system.addParticle(p);
   
   Evolver evolver(system);
   double dt = 0.01;
   double rcut = 0.5;
   evolver.setTimeStep(dt);
   evolver.setGlobalRcut(rcut);
   
   std::map<std::string, double> selfPropParams = {{"alpha", 2.0}};
   // std::map<std::string, double> polarAlignmentParams = {{"R", 2.0}, {"k", 1.2}};
   std::map<std::string, double> activeIntegratorParams = {{"Dpos", 2.0}, {"Drot", 1.2}, {"gammaPos", 1.2}, {"gammaRot", 1.2}, {"hasNoise", true}};
   
   evolver.addIntegrator("ActiveMatterIntegrator", activeIntegratorParams);
   evolver.addForce("SelfPropulsionForce", selfPropParams);
   // evolver.addTorque("PolarAlignment", polarAlignmentParams);
   
   
   
   // EXPECT_EQ("PolarAlignment", evolver.getTorques()["PolarAlignment"]->getName());
   EXPECT_EQ("SelfPropulsionForce", evolver.getForces()["SelfPropulsionForce"]->getName());
   EXPECT_EQ("ActiveMatterIntegrator", evolver.getIntegrators()["ActiveMatterIntegrator"]->getName());
   
   double rx = particlesList[0].r.x;
   double ry = particlesList[0].r.y;
   
   evolver.evolve();

   EXPECT_FALSE(rx == system.getParticles()[0].r.x);
   EXPECT_FALSE(ry == system.getParticles()[0].r.y);

}

TEST(numericsTests, computeForcesWorks){

   // given
   Point2D pt1(2.0, 2.0);
   Point2D pt2(1.8, 1.8);
   Point2D pt3(2.2, 2.2);

   Point2D pt4(0.0, 0.0);
   Point2D pt5(0.2, 0.2);
   Point2D pt6(2.0, -2.0);
   Point2D pt7(-2.0, -2.0);

   int type = 0;
   Point2D v0(0.44, 0.27);

   double deg2rad = 3.14159265359 / 180.;
   double th = 20.0 * deg2rad;

   Point2D size(6.0, 6.0);

   double dt = 0.01;
   double rcut = 0.5;

   double rad = 1.0;
   Particle p1(type, pt1, th, v0, rad);
   Particle p2(type, pt2, th, v0, rad);
   Particle p3(type, pt3, th, v0, rad);
   Particle p4(type, pt4, th, v0, rad);
   Particle p5(type, pt5, th, v0, rad);
   Particle p6(type, pt6, th, v0, rad);
   Particle p7(type, pt7, th, v0, rad);

   std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6, p7};

   Box boxx(size);
   
   System system(boxx);

   for (Particle const& p : particlesList) system.addParticle(p);
   
   // when
   Evolver evolver(system);
   
   
   evolver.setTimeStep(dt);
   evolver.setGlobalRcut(rcut);
   
   std::map<std::string, double> selfPropParams = {{"alpha", 2.0}};
   std::map<std::string, double> activeIntegratorParams = {{"Dpos", 2.0}, {"Drot", 1.2}, {"gammaPos", 1.2}, {"gammaRot", 1.2}, {"hasNoise", false}};
   
   evolver.addIntegrator("ActiveMatterIntegrator", activeIntegratorParams);
   evolver.addForce("SelfPropulsionForce", selfPropParams);
   
   // then
   EXPECT_EQ("SelfPropulsionForce", evolver.getForces()["SelfPropulsionForce"]->getName());
   EXPECT_EQ("ActiveMatterIntegrator", evolver.getIntegrators()["ActiveMatterIntegrator"]->getName());

   EXPECT_EQ(0.0, system.getParticles()[0].f.x);
   EXPECT_EQ(0.0, system.getParticles()[0].f.y);
   
   evolver.evolve();

   EXPECT_TRUE(0.0 != system.getParticles()[0].f.x);
   EXPECT_TRUE(0.0 != system.getParticles()[0].f.y);

}

TEST(numericsTests, brownianThetaChanges){

   // given
   Point2D pt1(2.0, 2.0);
   Point2D pt2(1.8, 1.8);
   Point2D pt3(2.2, 2.2);

   Point2D pt4(0.0, 0.0);
   Point2D pt5(0.2, 0.2);
   Point2D pt6(2.0, -2.0);
   Point2D pt7(-2.0, -2.0);

   int type = 0;
   Point2D v0(0.44, 0.0);

   double deg2rad = 3.14159265359 / 180.;
   double th = 20.0 * deg2rad;

   Point2D size(6.0, 6.0);

   double dt = 0.01;
   double rcut = 0.5;

   double rad = 1.0;
   Particle p1(type, pt1, th, v0, rad);
   Particle p2(type, pt2, th, v0, rad);
   Particle p3(type, pt3, th, v0, rad);
   Particle p4(type, pt4, th, v0, rad);
   Particle p5(type, pt5, th, v0, rad);
   Particle p6(type, pt6, th, v0, rad);
   Particle p7(type, pt7, th, v0, rad);

   std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6, p7};

   Box boxx(size);
   
   System system(boxx);

   for (Particle const& p : particlesList) system.addParticle(p);
   
   // when
   Evolver evolver(system);
   
   
   evolver.setTimeStep(dt);
   evolver.setGlobalRcut(rcut);
   
   std::map<std::string, double> selfPropParams = {{"alpha", 2.0}};
   std::map<std::string, double> activeIntegratorParams = {{"Dpos", 2.0}, {"Drot", 1.2}, {"gammaPos", 1.2}, {"gammaRot", 1.2}, {"hasNoise", true}};
   
   evolver.addIntegrator("ActiveMatterIntegrator", activeIntegratorParams);
   evolver.addForce("SelfPropulsionForce", selfPropParams);
   
   // then
   EXPECT_EQ("SelfPropulsionForce", evolver.getForces()["SelfPropulsionForce"]->getName());
   EXPECT_EQ("ActiveMatterIntegrator", evolver.getIntegrators()["ActiveMatterIntegrator"]->getName());

   EXPECT_EQ(th, system.getParticles()[0].theta);
   EXPECT_EQ(0.0, system.getParticles()[0].t);
   
   evolver.evolve();

   EXPECT_TRUE(th != system.getParticles()[0].theta);
   EXPECT_EQ(0.0, system.getParticles()[0].t);

}

TEST(numericsTests, wcaTwoSpheresOutsideCutoffWorks){

   // given
   Point2D pt1(1.0, 0.0);
   Point2D pt2(3.26, 0.0);

   int type = 0;
   Point2D v0(0.0, 0.0);

   double deg2rad = 3.14159265359 / 180.;
   double th = 20.0 * deg2rad;

   Point2D size(10.0, 10.0);

   double dt = 0.01;
   double rcut = 2.25;

   double rad = 1.0;
   Particle p1(type, pt1, th, v0, rad);
   Particle p2(type, pt2, th, v0, rad);

   std::vector <Particle> particlesList{p1, p2};

   Box boxx(size);
   
   System system(boxx);

   for (Particle const& p : particlesList) system.addParticle(p);
   
   // when
   Evolver evolver(system);
   
   
   evolver.setTimeStep(dt);
   evolver.setGlobalRcut(rcut);
   
   std::map<std::string, double> activeIntegratorParams = {{"Dpos", 2.0}, {"Drot", 1.2}, {"gammaPos", 1.2}, {"gammaRot", 1.2}, {"hasNoise", false}};
   std::map<std::string, double> wcaParams = {{"epsilon", 2.0}, {"sigma", 2.0}, {"dr", 0.01}, {"rcut", 2.25}};
   
   evolver.addIntegrator("ActiveMatterIntegrator", activeIntegratorParams);
   evolver.addForce("WCA", wcaParams);
   
   // then
   EXPECT_EQ("WCA", evolver.getForces()["WCA"]->getName());
   EXPECT_EQ("ActiveMatterIntegrator", evolver.getIntegrators()["ActiveMatterIntegrator"]->getName());

   EXPECT_EQ(th, system.getParticles()[0].theta);
   EXPECT_EQ(0.0, system.getParticles()[0].t);

   EXPECT_EQ(p1.r.x, system.getParticles()[0].r.x);
   EXPECT_EQ(p1.r.y, system.getParticles()[0].r.y);

   EXPECT_EQ(p2.r.x, system.getParticles()[1].r.x);
   EXPECT_EQ(p2.r.y, system.getParticles()[1].r.y);
   
   evolver.evolve();

   EXPECT_TRUE(th == system.getParticles()[0].theta);
   EXPECT_EQ(0.0, system.getParticles()[0].t);

   EXPECT_TRUE(th == system.getParticles()[1].theta);
   EXPECT_EQ(0.0, system.getParticles()[1].t);

   EXPECT_EQ(p1.r.x, system.getParticles()[0].r.x);
   EXPECT_EQ(p1.r.y, system.getParticles()[0].r.y);

   EXPECT_EQ(p2.r.x, system.getParticles()[1].r.x);
   EXPECT_EQ(p2.r.y, system.getParticles()[1].r.y);

}