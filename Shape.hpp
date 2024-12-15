#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include "Point.hpp"
#include "Vectors.hpp"
#include <string>


namespace Shapes {

    constexpr double PI = 3.141592653589793;

    // base class for a general shape
    class Shape {
    protected:
        std::string name;

    public:
        Shape(std::string name = "Default");

        virtual double area() const;
        virtual double circumference() const;
        std::string getName() const;
    };

    // circle shape class
    class Circle : public Shape {
    private:
        Point origin;
        double radius;

    public:
        // constructs a circle from an origin and a radius
        Circle(double radius, const Point& o);

        // circle area 
        double area() const override;

        // circle circumference 
        double circumference() const override;

        // circle bounding box 
        std::vector<Point> boundingBox() const;

        // creates a string summarizing the bounding box 
        std::string boundingBoxString();

        // summarizes the circle statistics
        void display();
    };

    // rectangle shape class   
    class Rectangle : public Shape {
    private:
        Point v1, v2, v3, v4;

    public:
        // constructs a rectangle from 4 vertices
        // verts must describe a shape with 4 right angles
        Rectangle(const Point& topLeft, const Point& topRight, const Point& bottomRight, const Point& bottomLeft);

        // rectangle area
        double area() const override;

        // rectangle perimeter
        double circumference() const override;

        // returns the vertices of the rectangle
        std::vector<Point> boundingBox() const;

        // string summary of the rectangle bounding box
        std::string boundingBoxString();

        // summarizes the rectangle statistics
        void display();
    };

    // triangle shape class 
    class Triangle : public Shape {
    private:
        Point v1, v2, v3;
        Point v1_v2, v1_v3, v3_v2;
        double v1_v3_length, v1_v2_length, v3_v2_length;

    public:
        // constructs a triangle from 3 vertices
        // vertices must be at unique positions to form a triangle
        Triangle(const Point& p1, const Point& p2, const Point& p3);

        // triangle area formula
        double area() const override;

        // triangle perimeter
        double circumference() const override;

        // calculates a base length for the triangle
        double getBase() const;

        // calculates a height for the triangle
        double getHeight() const;

        // calculates a bounding box for the triangle
        std::vector<Point> boundingBox() const;

        std::string boundingBoxString();

        // summarizes the triangle statistics
        void display();
    };

} // namespace Shapes

#endif
