#ifndef __particle_hpp__
#define __particle_hpp__

#include "Point2D.hpp"
#include <cmath>

struct Particle
{
    
    int id;
    int type;
    Point2D r; // position
    Point2D n; // direction vector (|n| = 1)
    double theta; //direction
    Point2D f; // force acting on the particle
    Point2D v; // velocity
    double m; //mass
    double t; //torque
    double e; //energy
    double rad; //radius

    Particle(int& type, Point2D &rr, double &th, Point2D v0, double &radius) : type{type}, r{rr}, theta{th}, v{v0}, rad{radius}{
        t = 0.0;
        f.x = 0.0; 
        f.y = 0.0;
        m = 1.0;
        rad = 1.0;
        n = Point2D(std::cos(theta), std::sin(theta));
    }
};


#endif
