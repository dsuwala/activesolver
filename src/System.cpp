#include "System.hpp"

System::System(const Box& boxx) : _box{boxx} {
    _particles.clear();
    _random = std::make_unique<RandomClass> (1231422);
    }

void System::applyPeriodic(){

    // bool allRinBox = false;

    // while(true){
        for (Particle& p : _particles){

            // double rx = p.r.x;
            // double ry = p.r.y;

            // apply pbc position shifts until particle will be inside box
            while(p.r.x > _box.Lmax.x || p.r.x < _box.Lmin.x){

                if (p.r.x < _box.Lmin.x) p.r.x += _box.L.x;
                if (p.r.x > _box.Lmax.x) p.r.x -= _box.L.x;
                
                // std::cerr << "Trying to move particle " << p.id << " into box" << '\n';
                // std::cerr << "current position x:" << p.r.x << " y:" << p.r.y << '\n';
                // std::cerr << "current force x:" << p.f.x << " y:" << p.f.y << '\n';
            }

            while(p.r.y > _box.Lmax.y || p.r.y < _box.Lmin.y){

                if (p.r.y < _box.Lmin.y) p.r.y += _box.L.y;
                if (p.r.y > _box.Lmax.y) p.r.y -= _box.L.y;

                // std::cerr << "Trying to move particle " << p.id << " into box" << '\n';
                // std::cerr << "current position x:" << p.r.x << " y:" << p.r.y << '\n';
                // std::cerr << "current force x:" << p.f.x << " y:" << p.f.y << '\n';
            }

            // if (rx < _box.Lmin.x) p.r.x = rx + _box.L.x;
            // if (rx > _box.Lmax.x) p.r.x = rx - _box.L.x;

            // if (ry < _box.Lmin.y) p.r.y = (ry / _box.L.y - std::floor(ry / _box.L.y)) * _box.L.y;
            // if (ry > _box.Lmax.y) p.r.y = (ry / _box.L.y - std::floor(ry / _box.L.y)) * _box.L.y;

        }

    // }
}

void System::applyHardWall(){

    for (Particle& p : _particles){

        // reflection according to the law of reflection 
        // if (p.r.magnitude() >= _box.L.magnitude()){
        //     p.theta += _PI / 2.0;
        // }
        
        // random reflection
        if (p.r.x <= _box.Lmin.x || p.r.x >= _box.Lmax.x){
            p.theta += _random->randreal(- _PI, 0);
        }
        if (p.r.y <= _box.Lmin.y || p.r.y >= _box.Lmax.y){
            p.theta += _random->randreal(- _PI / 2.0, _PI / 2.0);
        }
        
    }
}

void System::addParticle(const Particle& p){
    _particles.push_back(p);
    _particles[_numparticles].id = static_cast<int>(_numparticles);
    _numparticles++;
}

void System::initializeCellList(double rcut){

    _bucketList.clear();
    
    _Nx = static_cast<int>(_box.L.x/rcut);
    _Ny = static_cast<int>(_box.L.y/rcut);
    _numCells = _Nx*_Ny;
    _lx = _box.L.x/_Nx;
    _ly = _box.L.y/_Ny;   
    _bucketList.resize(_numCells);

}

int System::getIndex(int nx, int ny) const{

    //pbc
    if(nx>_Nx-1) nx = 0;
    if(nx<0) nx = _Nx - 1;
    if(ny>_Ny-1) ny = 0;
    if(ny<0) ny = _Ny - 1;

    return(nx+ny*_Nx);

}

void System::calculateNeighborList(double rcut){

    _neighborList.clear();
    for (int id = 0; id < _numparticles; id++){

        _neighborList.emplace_back(calculateNeighbors(id, rcut));
    }

}

std::vector<int> System::calculateNeighbors(int pid, double rcut){
//returns ids of particles inside neighbors of a cell corresponding to given pid

    std::vector <int> neighbors;
    double Lx = _box.L.x;
    double Ly = _box.L.y;

    auto nx = static_cast<int>((_particles[pid].r.x + Lx / 2.) / _lx);
    auto ny = static_cast<int>((_particles[pid].r.y + Ly / 2.) / _ly);
    
    for(auto i = -1; i<=1; i++){
        
        for(auto j = -1; j<=1; j++){

            //get neighbor bucket index and add particles inside it into neighbors
            auto cellindexNg = getIndex(nx+i, ny+j);
            for (int const& ng : _bucketList[cellindexNg]){

                // check if current neighbor is within rcut
                Point2D rij = _particles[pid].r - _particles[ng].r; 
                double rij_x = rij.x;
                double rij_y = rij.y;
                double boxSizeX = _box.L.x;
                double boxSizeY = _box.L.y;

                if (rij_x > boxSizeX * 0.5 ) rij.setX(rij_x - boxSizeX);
                if (rij_x <= - boxSizeX * 0.5 ) rij.setX(rij_x + boxSizeX);

                if (rij_y > boxSizeY * 0.5 ) rij.setY(rij_y - boxSizeY);
                if (rij_y <= - boxSizeY * 0.5 ) rij.setY(rij_y + boxSizeY);

                // itself is accepted as neighbor
                if ( rij.magnitude() <= rcut){
                    
                    neighbors.push_back(ng);
                }
            }
        }
    }

    return neighbors; 
}

void System::fillCellList(){

    int i;
    int j;
    int k;

    double Lx = _box.L.x;
    double Ly = _box.L.y;
    
    // std::cerr << "particles size: " << _particles.size() << '\n';

    for (int id = 0; id < _numparticles; id++){

        // particle coordinates are shifted by L/2 not to have negative indices
        i = static_cast<int>((_particles.at(id).r.x + Lx / 2.) / _lx);
        j = static_cast<int>((_particles.at(id).r.y + Ly / 2.) / _ly);

        k = i + j * _Nx; // index of the cell

        _bucketList[k].push_back(id);

    }
}
