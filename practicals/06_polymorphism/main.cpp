// Practical 06 - Runtime Polymorphism and Abstract Classes
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Shape is abstract (it has a pure virtual area()). Circle, Rectangle and
// Triangle override area(). We call area() through Shape pointers, and the
// correct derived version runs at RUNTIME (dynamic dispatch via vtable).

#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual double area() const = 0;        // pure virtual -> abstract class
    virtual const char* name() const = 0;
    virtual ~Shape() = default;             // virtual dtor: safe deletion
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159265 * r_ * r_; }
    const char* name() const override { return "Circle"; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    const char* name() const override { return "Rectangle"; }
};

class Triangle : public Shape {
    double base_, height_;
public:
    Triangle(double b, double h) : base_(b), height_(h) {}
    double area() const override { return 0.5 * base_ * height_; }
    const char* name() const override { return "Triangle"; }
};

int main() {
    // Store different shapes behind a common base-class pointer.
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 8.0));

    std::cout << "=== Areas computed via base-class interface ===\n";
    for (const auto& shape : shapes) {
        // Same call, different behaviour chosen at runtime:
        std::cout << "  " << shape->name()
                  << " area = " << shape->area() << '\n';
    }

    // Shape s;  // <- COMPILE ERROR: cannot instantiate an abstract class,
    //              because area() has no implementation in Shape.
    std::cout << "\nShape itself is abstract and cannot be instantiated.\n";
    return 0;
}
