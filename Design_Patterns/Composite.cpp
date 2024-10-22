#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual void draw() const = 0; 
    virtual ~Shape() = default; 
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle\n";
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Rectangle\n";
    }
};

class CompositeShape : public Shape {
private:
    std::vector<std::shared_ptr<Shape>> shapes; 

public:
    void addShape(const std::shared_ptr<Shape>& shape) {
        shapes.push_back(shape);
    }

    void draw() const override {
        std::cout << "Drawing a Composite Shape consisting of:\n";
        for (const auto& shape : shapes) {
            shape->draw(); 
        }
    }
};

int main() {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>();
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>();

    CompositeShape compositeShape;
    compositeShape.addShape(circle1);
    compositeShape.addShape(rectangle1);

    compositeShape.draw();

    CompositeShape largerComposite;
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>();
    largerComposite.addShape(circle2);
    largerComposite.addShape(std::make_shared<Circle>());
    largerComposite.addShape(std::make_shared<Rectangle>());
    largerComposite.addShape(std::make_shared<Rectangle>());

    largerComposite.draw();

    return 0;
}
