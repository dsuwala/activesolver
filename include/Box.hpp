#ifndef __box_hpp__
#define __box_hpp__

#include "Point2D.hpp"

struct Box
{

    Point2D L; // box size in x and y directions
    Point2D Lmin; // minimal x, y values
    Point2D Lmax; // maximal x, y values
    
    explicit Box(Point2D &l);
    Box() = default;

};

#endif
