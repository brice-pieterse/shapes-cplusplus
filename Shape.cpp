#include "Shape.hpp"
#include "Vectors.hpp"
#include <iostream>
#include <cmath>

using namespace Shapes;
using namespace Vectors;
using std::cout;
using std::endl;

Shape::Shape(std::string name): name(name) {}

double Shape::area() const {
    return 0;  // default behavior for a general shape
}

double Shape::circumference() const {
    return 0;  // default behavior for a general shape
}

std::string Shape::getName() const {
    return name;
}

Circle::Circle(double radius, const Point& o): Shape("circle"), origin(o), radius(radius) {
    // constructs a circle from an origin and a radius
    if (radius <= 0) {
        throw std::invalid_argument("Circles have a positive radius.");
    }
}

double Circle::area() const {
    return PI * radius * radius;  // area of circle formula
}

double Circle::circumference() const {
    return 2 * PI * radius;  // circumference of circle formula
}

std::vector<Point> Circle::boundingBox() const {
    // circle bounding box 
    std::vector<Point> bounds = {
        Point{origin.x() + radius, origin.y() + radius},
        Point{origin.x() - radius, origin.y() + radius},
        Point{origin.x() + radius, origin.y() - radius},
        Point{origin.x() - radius, origin.y() - radius}
    };
    return bounds;
}

std::string Circle::boundingBoxString() {
    // creates a string summarizing the bounding box 
    std::string str;
    std::vector<Point> box = boundingBox();
    for (size_t i = 0; i < box.size(); i++) {
        str += "(x: " + std::to_string(box[i].x());
        str += ", y: " + std::to_string(box[i].y()) + ")";
    }
    return str;
}

void Circle::display() {
    // summarizes the circle statistics
    cout << "Shape with name: " + getName() + 
    "; area: " + std::to_string(area()) +
    "; circumference: " + std::to_string(circumference()) +
    "; bounding box: " + boundingBoxString() << endl;
}

Rectangle::Rectangle(const Point& topLeft, const Point& topRight, const Point& bottomRight, const Point& bottomLeft): 
    Shape("rectangle"), v1(topLeft), v2(topRight), v3(bottomRight), v4(bottomLeft) {
    // constructs a rectangle from 4 vertices
    // verts must describe a shape with 4 right angles
    if (
        dot(subVectors(topLeft, topRight), subVectors(bottomLeft, topLeft)) != 0 ||
        dot(subVectors(bottomRight, topRight), subVectors(bottomRight, bottomLeft)) != 0
    ) {
        throw std::invalid_argument("Rectangles have four right angles.");
    }
}

double Rectangle::area() const {
    // rectangle area
    return vecLength(subVectors(v1, v2)) * vecLength(subVectors(v1, v4));
}

double Rectangle::circumference() const {
    // rectangle perimeter
    return 2 * vecLength(subVectors(v1, v2)) + 2 * vecLength(subVectors(v1, v4));
}

std::vector<Point> Rectangle::boundingBox() const {
    // returns the vertices of the rectangle
    std::vector<Point> bounds = { v1, v2, v3, v4 };
    return bounds;
}

std::string Rectangle::boundingBoxString() {
    // string summary of the rectangle bounding box
    std::string str;
    std::vector<Point> box = boundingBox();
    for (size_t i = 0; i < box.size(); i++) {
        str += "(x: " + std::to_string(box[i].x());
        str += ", y: " + std::to_string(box[i].y()) + ")";
    }
    return str;
}

void Rectangle::display() {
    // summarizes the rectangle statistics
    cout << "Shape with name: " + getName() + 
    "; area: " + std::to_string(area()) +
    "; circumference: " + std::to_string(circumference()) +
    "; bounding box: " + boundingBoxString() << endl;
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3): v1(p1), v2(p2), v3(p3) {
    // constructs a triangle from 3 vertices
    v1_v2 = Point{v2.x() - v1.x(), v2.y() - v1.y()};
    v1_v3 = Point{v3.x() - v1.x(), v3.y() - v1.y()};
    v3_v2 = Point{v3.x() - v2.x(), v3.y() - v2.y()};

    if (vectorEquality(v1, v2) || vectorEquality(v1, v3) || vectorEquality(v3, v2)) {
        throw std::invalid_argument("Vertices of the triangle must be at unique positions.");
    }

    v1_v3_length = vecLength(v1_v3);
    v1_v2_length = vecLength(v1_v2);
    v3_v2_length = vecLength(v3_v2);
}

double Triangle::area() const {
    // triangle area formula
    return (getBase() * getHeight()) / 2;
}

double Triangle::circumference() const {
    // triangle perimeter
    return v1_v3_length + v1_v2_length + v3_v2_length;
}

double Triangle::getBase() const {
    // calculates a base length for the triangle
    return v1_v2_length;
}

double Triangle::getHeight() const {
    // calculates a height for the triangle
    return vecLength(
        subVectors(proj_a_b(v1_v3, v1_v2), v1_v3)
    );
}

std::vector<Point> Triangle::boundingBox() const {
    // calculates a bounding box for the triangle
    Point fromBaseToTip = subVectors(proj_a_b(v1_v3, v1_v2), v1_v3);
    std::vector<Point> bounds = {
        Point{v1.x(), v1.y()},
        Point{v2.x(), v2.y()},
        Point{v1.x() + fromBaseToTip.x(), v1.y() + fromBaseToTip.y()},
        Point{v2.x() + fromBaseToTip.x(), v2.y() + fromBaseToTip.y()}
    };
    return bounds;
}

std::string Triangle::boundingBoxString() {
    std::string str;
    std::vector<Point> box = boundingBox();
    for (size_t i = 0; i < box.size(); i++) {
        str += "(x: " + std::to_string(box[i].x());
        str += ", y: " + std::to_string(box[i].y()) + ")";
    }
    return str;
}

void Triangle::display() {
    // summarizes the triangle statistics
    cout << "Shape with name: " + getName() + 
    "; area: " + std::to_string(area()) +
    "; circumference: " + std::to_string(circumference()) +
    "; bounding box: " + boundingBoxString() << endl;
}