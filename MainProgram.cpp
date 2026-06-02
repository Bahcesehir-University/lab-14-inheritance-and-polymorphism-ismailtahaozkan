// ============================================================
// MainProgram.cpp  —  TEACHER VERSION (full solution)
// Lab: Inheritance and Polymorphism
// Course: Object-Oriented Programming (C++)
// Standard: C++17  |  Single file only, no headers
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// ================================
// CLASS DEFINITIONS
// ================================

// --- Base class -------------------------------------------------
class Shape {
protected:
    std::string name;

public:
    Shape(const std::string& n) : name(n) {}

    // Virtual destructor: required for safe polymorphic deletion.
    virtual ~Shape() {}

    // Pure virtual -> Shape is abstract, cannot be instantiated.
    virtual double area() const = 0;

    // Virtual: derived classes may override; has a default body.
    virtual std::string describe() const {
        return name + " with area " + std::to_string(area());
    }

    std::string getName() const { return name; }
};

// --- Derived class: Circle --------------------------------------
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}

    double area() const override {
        return 3.14159265358979323846 * radius * radius;
    }
};

// --- Derived class: Rectangle -----------------------------------
class Rectangle : public Shape {
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h)
        : Shape("Rectangle"), width(w), height(h) {}

    double area() const override {
        return width * height;
    }
};

// --- Derived class: Square (inherits from Rectangle) ------------
class Square : public Rectangle {
public:
    Square(double side) : Rectangle(side, side) {
        name = "Square"; // refine the inherited name
    }

    // Demonstrates overriding an already-overridden virtual.
    std::string describe() const override {
        return "Square (side based) with area " + std::to_string(area());
    }
};

// ================================
// FUNCTION IMPLEMENTATIONS
// ================================

// Polymorphic free function: works on any Shape via base pointer.
double totalArea(const std::vector<Shape*>& shapes) {
    double sum = 0.0;
    for (const Shape* s : shapes) {
        sum += s->area(); // dynamic dispatch
    }
    return sum;
}

// Returns the name of the shape with the largest area.
// Returns "" for an empty container.
std::string largestShapeName(const std::vector<Shape*>& shapes) {
    if (shapes.empty()) return "";
    const Shape* biggest = shapes[0];
    for (const Shape* s : shapes) {
        if (s->area() > biggest->area()) {
            biggest = s;
        }
    }
    return biggest->getName();
}

// ================================
// MAIN
// ================================
int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(2.0));
    shapes.push_back(new Rectangle(3.0, 4.0));
    shapes.push_back(new Square(5.0));

    for (const Shape* s : shapes) {
        std::cout << s->describe() << std::endl;
    }

    std::cout << "Total area: " << totalArea(shapes) << std::endl;
    std::cout << "Largest:    " << largestShapeName(shapes) << std::endl;

    for (Shape* s : shapes) delete s;
    return 0;
}
