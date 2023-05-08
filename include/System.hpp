#ifndef __system_hpp__
#define __system_hpp__

#include "Particle.hpp"
#include "Box.hpp"
#include "RandomClass.hpp"
#include <iostream>

#include <vector> 
#include <map>
#include <memory>

class System
{

    public:
        explicit System(const Box& boxx);
        ~System() = default;

        // * Apply pbc for entire particle list
        void applyPeriodic();
        
        // apply reflective wall bc for entire particle list
        void applyHardWall();

        void addParticle(const Particle& p);

        void fillCellList(); 
        void initializeCellList(double rcut);
        int getIndex(int nx, int ny) const;

        void calculateNeighborList(double rcut);
        std::vector <int> calculateNeighbors(int pid, double rcut);

        std::vector <Particle>& getParticles() {return _particles;}
        std::vector <std::vector <int>>& getNeighbors() {return _neighborList;}
        std::vector <std::vector <int>>& getBuckets() {return _bucketList;}
        
        Box getBox() const {return _box;}
        long unsigned int getSize() const {return _numparticles;}

    private:

        std::vector <Particle> _particles;
        const Box& _box;
        long unsigned int _numparticles = 0;
        std::vector <std::vector <int>> _bucketList; //store buckets of ids of particles the same cell
        std::vector <std::vector <int>> _neighborList; //store buckets of ids of particles the same cell

        
        //size of buckets in each direction in the bucket list
        double _lx;
        double _ly; 

        int _numCells; //Total number of cells
        
        // Number of cells in X and Y
        int _Nx;
        int _Ny; 
        
        double _PI = 3.14159265359;
        std::unique_ptr<RandomClass> _random;

};

#endif
