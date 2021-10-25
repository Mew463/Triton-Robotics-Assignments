#include <iostream>
#include <cmath>

using namespace std;

class Point2d {
public:
    double m_x;
    double m_y;

    Point2d() {
        m_x = 0.0;
        m_y = 0.0;
    } 

    Point2d(double x, double y) {
        m_x = x;
        m_y = y;
    } 

    double getX() {
        return m_x;
    }

    double getY() {
        return m_y;
    }

    double distanceTo(Point2d otherCoord) {
        double x1 = m_x;
        double x2 = otherCoord.getX();
        double y1 = m_y;
        double y2 = otherCoord.getY();
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    void print() {
        cout << "Point2d(" << m_x << ", " << m_y << ")" << endl;
    }

};

double distanceFrom(Point2d firstCoord, Point2d secondCoord) {
        double x1 = firstCoord.getX();
        double x2 = secondCoord.getX();
        double y1 = firstCoord.getY();
        double y2 = secondCoord.getY();
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }


int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };
    first.print();
    second.print();
    cout << "Distance between two points: " << distanceFrom(first, second) << '\n';

    return 0;
}