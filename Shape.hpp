#include <vector>
#include <iostream>
#include "Point.hpp"
#include "Vectors.hpp"

using std::vector;
using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::sqrt;
using std::acos;
using std::sin;

using Vectors::dot;
using Vectors::proj_a_b;
using Vectors::vecLength;
using Vectors::vectorEquality;
using Vectors::subVectors;

#include <cmath>


namespace Shapes {

    constexpr double PI = 3.141592653589793;

    // base class for a general shape
    class Shape {
        string name;

        public:
            Shape(string name = "Default"): name(name) {}

            double area(){
                return 0;
            };

            string getName(){
                return name;
            };

            double circumference(){
                return 0;
            };

    };

    // circle shape class
    class Circle: public Shape {
        
        Point origin;
        double radius;

        public:
            // constructs a circle from an origin and a radius
            Circle(double radius, const Point& o): Shape("circle"), origin(o), radius(radius) {
                if(radius <= 0){
                    throw std::invalid_argument("Circles have a positive radius.");
                }
            };

            // circle area 
            double area() const {
                return PI * radius * radius;
            };

            // circle circumference 
            double circumference() const {
                return 2 * PI * radius;
            };

            // circle bounding box 
            vector<Point> boundingBox() const {
                cout << "here" << endl;
                vector<Point> bounds = {
                    Point{origin.x() + radius, origin.y() + radius},
                    Point{origin.x() - radius, origin.y() + radius},
                    Point{origin.x() + radius, origin.y() - radius},
                    Point{origin.x() - radius, origin.y() - radius}
                };
                cout << "after" << endl;
                return bounds;
            };

            // creates a string summarizing the bounding box 
            string boundingBoxString(){
                string str;
                vector<Point> box = boundingBox();
                cout << "box size" << endl;
                for(size_t i = 0; i < box.size(); i++){
                    str += "(x: " + to_string(box[i].x());
                    str += ", y: " + to_string(box[i].y()) + ")";
                }
                return str;
            }

            // summarizes the circle statistics
            void display(){
                cout << "Shape with name: " + getName() + 
                "; area: " + to_string(area()) +
                "; circumference: " + to_string(circumference()) +
                "; bounding box: " + boundingBoxString() << endl;
            };
    }; 

    // rectangle shape class   
    class Rectangle: public Shape {

        Point v1;
        Point v2;
        Point v3;
        Point v4;

        public:
            // constructs a rectangle from 4 verticles
            // verts must describe a shape with 4 right angles
            Rectangle(const Point&topLeft, const Point&topRight, const Point&bottomRight, const Point&bottomLeft): 
            Shape("rectangle"), v1(topLeft), v2(topRight), v3(bottomRight), v4(bottomLeft) {
                
                // check that the shape is a rectange
                if(
                    dot(subVectors(topLeft, topRight), subVectors(bottomLeft, topLeft)) != 0 ||
                    dot(subVectors(bottomRight, topRight), subVectors(bottomRight, bottomLeft)) != 0
                ){
                    throw std::invalid_argument("Rectangles have four right angles.");
                }
                
            };

            // rectangle area
            double area() const {
                return vecLength(subVectors(v1, v2)) * vecLength(subVectors(v1, v4));
            };

            // rectangle perimeter
            double circumference() const {
                return 2 * vecLength(subVectors(v1, v2)) + 2 * vecLength(subVectors(v1, v4));
            };

            // returns the vertices of the rectangle
            vector<Point> boundingBox() const {
                vector<Point> bounds = { v1, v2, v3, v4 };
                return bounds;
            };

            // string summary of the rectangle bounding box
            string boundingBoxString(){
                string str;
                vector<Point> box = boundingBox();
                for(size_t i = 0; i < box.size(); i++){
                    str += "(x: " + to_string(box[i].x());
                    str += ", y: " + to_string(box[i].y()) + ")";
                }
                return str;
            }

            // summarizes the rectangle statistics
            void display(){
                cout << "Shape with name: " + getName() + 
                "; area: " + to_string(area()) +
                "; circumference: " + to_string(circumference()) +
                "; bounding box: " + boundingBoxString() << endl;
            };

    }; 

    // triangle shape class 
    class Triangle: public Shape {

        Point v1;
        Point v2;
        Point v3;

        Point v1_v2;
        Point v1_v3;
        Point v3_v2;

        double v1_v3_length;
        double v1_v2_length;
        double v3_v2_length;

        public:
            // constructs a triangle from 3 vertices
            // vertices must be at unique positions to form a triangle
            Triangle(const Point&p1, const Point&p2, const Point&p3): v1(p1), v2(p2), v3(p3) {

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

            // triangle area formula
            double area() const {
                return (getBase() * getHeight())/2;
            };

            // triangle perimeter
            double circumference() const {
                return v1_v3_length + v1_v2_length + v3_v2_length;
            };

            // calculates a base length for the triangle
            double getBase() const {
                return v1_v2_length;
            }

            // calculates a height for the triangle
            double getHeight() const {
                return vecLength(
                    subVectors( proj_a_b(v1_v3, v1_v2), v1_v3 )
                );
            }

            // calculates a bounding box for the triangle
            vector<Point> boundingBox() const{
                Point fromBaseToTip = subVectors(proj_a_b(v1_v3, v1_v2), v1_v3);
                vector<Point> bounds = {
                    Point{v1.x(), v1.y()},
                    Point{v2.x(), v2.y()},
                    Point{v1.x() + fromBaseToTip.x(), v1.y() + fromBaseToTip.y()},
                    Point{v2.x() + fromBaseToTip.x(), v2.y() + fromBaseToTip.y()}
                };
                return bounds;
            };

            
            string boundingBoxString(){
                string str;
                vector<Point> box = boundingBox();
                for(size_t i = 0; i < box.size(); i++){
                    str += "(x: " + to_string(box[i].x());
                    str += ", y: " + to_string(box[i].y()) + ")";
                }
                return str;
            }


            // summarizes the triangle statistics
            void display(){
                cout << "Shape with name: " + getName() + 
                "; area: " + to_string(area()) +
                "; circumference: " + to_string(circumference()) +
                "; bounding box: " + boundingBoxString() << endl;
            };
    };   
}