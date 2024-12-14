#include <vector>

using std::vector;

// a class describing a two dimensional point

class Point {
    vector<double> p;

    public:

        Point(){ p = { 0, 0 }; }
        Point(double x, double y): p({x, y}) {}
        // compiler supplies a copy constructor
        // Point(const Point& xy): p(xy.p) {}

        const vector<double> show() const {
            return p;
        }

        void add(double x, double y){
            p[0] += x;
            p[1] += y;
        }

        void subtract(double x, double y){
            p[0] -= x;
            p[1] -= y;
        }

        vector<double> copy() {
            return p;
        }

        double x() const {
            return p.at(0);
        }

        double y() const {
            return p.at(1);
        }
};