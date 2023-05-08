#ifndef __point2d_hpp__
#define __point2d_hpp__

#include <cmath>

class Point2D{
    public:
        /*! Create 2D vector of doubles witch supported vector operations: magnitude, 
        vector addition/subtraction +/-, dot product *, vector boolean comparison by magnitude >/< and 
        scaling by scalar *= and /=
        */
        Point2D(double x, double y);
        Point2D() = default;

        ~Point2D() = default;

        double magnitude() const;
        
        /*! Performs elementwise addition of vector elements and returns new vector
        */
        Point2D operator+(const Point2D &other);

        /*! Performs elementwise subtraction of provided vector from target vector
        and returns new vector
        */
        Point2D operator-(const Point2D &other);

        /*! Returns new vector as dot product of two provided vectors 
        */
        double operator*(const Point2D &other) const; 

        /*! Returns true if target vector has smaller magnitude than other provided as 
        an argument
        */ 
        bool operator<(const Point2D &other) const;

        /*! Returns true if target vector has greater magnitude than 
        other provided as an argument
        */ 
        bool operator>(const Point2D &other) const;

        /*! Performs elementwise division of targed vector by provided scalar
        */
        Point2D operator/(const double &other); 

        /*! Performs elementwise multiplication of targed vector by provided scalar
        */
        Point2D operator*(const double &other);


        //double getX(){return x;}
        //double getY(){return y;}
        double setX(double xx){return x = xx;}
        double setY(double yy){return y = yy;}

        double x;
        double y; 
    private:
};
#endif /* VECTORCLASS_HPP */
