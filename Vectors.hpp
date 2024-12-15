#ifndef VECTORS_HPP
#define VECTORS_HPP

#include "Point.hpp"

namespace Vectors {

    double square(const double& i);

    // checks for equality of the vector components
    bool vectorEquality(const Point& a, const Point& b);

    // calculates vector length
    double vecLength(const Point& a);

    // subtracts vector a from vector b (a -> b)
    Point subVectors(const Point& a, const Point& b);

    // calculates dot product of two vectors
    double dot(const Point& a, const Point& b);

    // calculates the vector projection of a onto b
    Point proj_a_b(const Point& a, const Point& b);

}

#endif