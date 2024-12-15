#include <iostream>
#include <memory>

class Color {
public:
    virtual ~Color() = default;
    virtual std::string getColor() const = 0;
};

class Red : public Color {
public:
    std::string getColor() const override { return "Red"; }
};

class Blue : public Color {
public:
    std::string getColor() const override { return "Blue"; }
};

class Shape {
protected:
    std::shared_ptr<Color> color;
public:
    explicit Shape(std::shared_ptr<Color> color) : color(color) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(std::shared_ptr<Color> color) : Shape(color) {}
    void draw() const override {
        std::cout << "Drawing a " << color->getColor() << " Circle.\n";
    }
};

class Rectangle : public Shape {
public:
    explicit Rectangle(std::shared_ptr<Color> color) : Shape(color) {}
    void draw() const override {
        std::cout << "Drawing a " << color->getColor() << " Rectangle.\n";
    }
};

int main() {
    auto red = std::make_shared<Red>();
    auto blue = std::make_shared<Blue>();

    auto redCircle = std::make_shared<Circle>(red);
    auto blueRectangle = std::make_shared<Rectangle>(blue);

    redCircle->draw();
    blueRectangle->draw();

    return 0;
}
