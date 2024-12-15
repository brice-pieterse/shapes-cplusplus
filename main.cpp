#include <iostream>
#include "Shape.hpp"

using Shapes::Shape;
using Shapes::Circle;
using Shapes::Rectangle;
using Shapes::Triangle;
using std::cout;
using std::endl;

/* 

Assignment 2
Brice Pieterse
3666099
December 14, 2024

Goal: Create an inheritance hierarchy of Shapes using a Point class to describe their geometry. Create methods to calculate area, perimeter, etc.

Test Plan:

- Try to construct some degenerate shapes (ie. Circle with negative radius)
- Validate statistics of valid shapes (area, perimeter, etc.)

*/

int main(){
    Shape s;
    Circle c { 10.0, Point{0, 0} };
    Rectangle r { Point{-1, 1}, Point{1, 1}, Point{1, -1}, Point{-1, -1} };
    Triangle t { Point{-1, 1}, Point{1, 1}, Point{-1, -1} };


    // testing shape methods
    cout << "Testing circle methods" << endl;
    c.display();

    cout << "Testing rectangle methods" << endl;
    r.display();

    cout << "Testing triangle methods" << endl;
    t.display();


    // testing invalid shapes
    try {
        Circle c_wrong { 0.0, Point{0, 0} };
    } catch (const std::invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    try {
        Rectangle r_wrong { Point{-1, 1}, Point{1, 0.5}, Point{1, -1}, Point{-1, -1} };
    } catch (const std::invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    try {
        Triangle t_wrong { Point{-1, 1}, Point{-1, 1}, Point{-1, -1} };
    } catch (const std::invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    return 0;
}