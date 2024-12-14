#include "Point.hpp"

namespace Vectors {

    double square(const double& i){
        return i * i;
    }


    // checks for equality of the vector components
    bool vectorEquality(const Point& a, const Point& b) {
        return (a.x() == b.x()) && (a.y() == b.y()); 
    }

    // calculates vector length
    double vecLength(const Point& a) {
        return sqrt(square(a.x()) + square(a.y()));
    }

    // subtracts vector a from vector b (a -> b)
    Point subVectors(const Point& a, const Point& b) {
        Point newV = { b.x() - a.x(), b.y() - a.y() };
        return newV;
    }

    // calculates dot product of two vectors
    double dot(const Point& a, const Point& b) {
        return a.x() * b.x() + a.y() * b.y(); 
    }

    // calculates the vector projection of a onto b
    Point proj_a_b(const Point& a, const Point& b) {
        double scale = dot(a, b)/(square(vecLength(b)));
        Point proj{ scale * b.x(), scale * b.y() };
        return proj;
    }

}