// Practical 08 - Factory Design Pattern
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Chosen pattern: FACTORY.
// Why it fits: we want to create different Shape objects from a simple type
// name (e.g. read from a menu or a file) without the caller using 'new' on a
// concrete class. The factory centralizes object creation.
//
// Benefit : adding a new shape only changes the factory, not every caller.
// Trade-off: an extra layer of indirection / structure to maintain.

#include <iostream>
#include <memory>
#include <string>

class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override { std::cout << "  Drawing a Circle\n"; }
};
class Square : public Shape {
public:
    void draw() const override { std::cout << "  Drawing a Square\n"; }
};
class Triangle : public Shape {
public:
    void draw() const override { std::cout << "  Drawing a Triangle\n"; }
};

// The Factory: returns a Shape based on the requested type.
class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(const std::string& type) {
        if (type == "circle")   return std::make_unique<Circle>();
        if (type == "square")   return std::make_unique<Square>();
        if (type == "triangle") return std::make_unique<Triangle>();
        return nullptr;   // unknown type
    }
};

int main() {
    std::cout << "=== Factory creating shapes by name ===\n";
    const std::string requests[] = {"circle", "square", "triangle", "hexagon"};

    for (const std::string& type : requests) {
        auto shape = ShapeFactory::create(type);
        if (shape) {
            shape->draw();
        } else {
            std::cout << "  Unknown shape type: " << type << '\n';
        }
    }
    return 0;
}
