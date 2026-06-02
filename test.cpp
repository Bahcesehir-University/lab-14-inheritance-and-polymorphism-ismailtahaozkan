// ============================================================
// test.cpp  —  Catch2 tests for Inheritance & Polymorphism lab
// ============================================================
// Tag-based grouping enables partial credit:
//   ./test_bin [t1] ... [t6]   (Linux autograder)
//   make test_1 ... make test_6
// ============================================================

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

// Pull in the student's implementation. Rename their main to avoid clash.
#define main student_main
#include "MainProgram.cpp"
#undef main

// ------------------------------------------------------------
// [t1] Circle::area  (normal + boundary)
// ------------------------------------------------------------
TEST_CASE("Circle area is computed correctly", "[t1]") {
    Circle c(2.0);
    REQUIRE(c.area() == Catch::Approx(12.56637061).epsilon(0.0001));

    Circle unit(1.0);
    REQUIRE(unit.area() == Catch::Approx(3.14159265).epsilon(0.0001));

    Circle zero(0.0);
    REQUIRE(zero.area() == Catch::Approx(0.0));
}

// ------------------------------------------------------------
// [t2] Rectangle::area  (normal + boundary)
// ------------------------------------------------------------
TEST_CASE("Rectangle area is computed correctly", "[t2]") {
    Rectangle r(3.0, 4.0);
    REQUIRE(r.area() == Catch::Approx(12.0));

    Rectangle thin(0.0, 10.0);
    REQUIRE(thin.area() == Catch::Approx(0.0));

    Rectangle big(100.0, 100.0);
    REQUIRE(big.area() == Catch::Approx(10000.0));
}

// ------------------------------------------------------------
// [t3] Square via inheritance from Rectangle
// ------------------------------------------------------------
TEST_CASE("Square inherits Rectangle and computes area", "[t3]") {
    Square s(5.0);
    REQUIRE(s.area() == Catch::Approx(25.0));
    REQUIRE(s.getName() == "Square");

    // A Square IS-A Shape: must bind to a base pointer.
    Shape* sp = new Square(3.0);
    REQUIRE(sp->area() == Catch::Approx(9.0));
    delete sp;
}

// ------------------------------------------------------------
// [t4] Polymorphism: dynamic dispatch through Shape*
// ------------------------------------------------------------
TEST_CASE("Virtual dispatch calls the correct override", "[t4]") {
    Shape* a = new Circle(1.0);
    Shape* b = new Rectangle(2.0, 5.0);

    REQUIRE(a->area() == Catch::Approx(3.14159265).epsilon(0.0001));
    REQUIRE(b->area() == Catch::Approx(10.0));

    delete a;
    delete b;
}

// ------------------------------------------------------------
// [t5] totalArea over a polymorphic container
// ------------------------------------------------------------
TEST_CASE("totalArea sums areas polymorphically", "[t5]") {
    std::vector<Shape*> v;
    v.push_back(new Rectangle(2.0, 3.0)); // 6
    v.push_back(new Square(4.0));         // 16
    REQUIRE(totalArea(v) == Catch::Approx(22.0));

    std::vector<Shape*> empty;
    REQUIRE(totalArea(empty) == Catch::Approx(0.0));

    for (Shape* s : v) delete s;
}

// ------------------------------------------------------------
// [t6] largestShapeName  (normal + empty edge case)
// ------------------------------------------------------------
TEST_CASE("largestShapeName finds the biggest shape", "[t6]") {
    std::vector<Shape*> v;
    v.push_back(new Circle(1.0));      // ~3.14
    v.push_back(new Rectangle(2.0, 2.0)); // 4
    v.push_back(new Square(10.0));     // 100
    REQUIRE(largestShapeName(v) == "Square");

    std::vector<Shape*> empty;
    REQUIRE(largestShapeName(empty) == "");

    for (Shape* s : v) delete s;
}
