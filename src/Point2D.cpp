#include "Point2D.hpp"

Point2D::Point2D(double x, double y){
    Point2D::setX(x);
    Point2D::setY(y);
}

double Point2D::magnitude() const{
    return std::sqrt(x * x + y * y);
}

Point2D Point2D::operator+(const Point2D &other){
    return Point2D(Point2D::x + other.x,
                       Point2D::y + other.y);
}

Point2D Point2D::operator-(const Point2D &other){
    return Point2D(Point2D::x - other.x,
                   Point2D::y - other.y);
}

double Point2D::operator*(const Point2D &other) const{
    return Point2D::x * other.x + 
           Point2D::y * other.y;
}

bool Point2D::operator<(const Point2D &other) const{
    double own_magnitude = magnitude();
    double other_magnitude = other.magnitude();
    if (own_magnitude >= other_magnitude){
        return false;
    }else{
        return true;
    }
}

bool Point2D::operator>(const Point2D &other) const{
    double own_magnitude = magnitude();
    double other_magnitude = other.magnitude();
    if (own_magnitude > other_magnitude){
        return true;
    }else{
        return false;
    }
}

Point2D Point2D::operator/(const double &other){
    return Point2D(x/ other,
                  y / other);
}

Point2D Point2D::operator*(const double &other) {
    return Point2D(x * other,
                   y * other);
}
