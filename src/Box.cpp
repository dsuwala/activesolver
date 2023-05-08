#include "Box.hpp"

Box::Box(Point2D &l) : L{l}{

    Lmax.x = l.x / 2.0;
    Lmax.y = l.x / 2.0;

    Lmin.x = - l.x / 2.0;
    Lmin.y = - l.y / 2.0;

}
