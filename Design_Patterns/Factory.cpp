#include <iostream>
#include <cmath>

struct Point {
private:
    float x, y;

    Point(const float x, const float y) : x(x), y(y) {}

public:
    struct PointFactory {
    private:
        PointFactory() {}

    public:
        static Point Cartesian(const float x, const float y) {
            return Point(x, y);
        }

        static Point Polar(const float r, const float alpha) {
            float x = r * std::cos(alpha);
            float y = r * std::sin(alpha);
            return Point(x, y);
        }
    };

    void display() const {
        std::cout << "Point Coordinates: (" << x << ", " << y << ")\n";
    }
};

int main() {
    Point cartesianPoint = Point::PointFactory::Cartesian(3.0, 4.0);
    cartesianPoint.display();

    Point polarPoint = Point::PointFactory::Polar(5.0, M_PI / 4);
    polarPoint.display();

    return 0;
}