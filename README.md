# Lab: Inheritance and Polymorphism

**Course:** Object-Oriented Programming (C++)
**Level:** 2nd-Year Engineering
**Duration:** 60 minutes
**Language standard:** C++17
**Structure:** Single file (`MainProgram.cpp`), no header files.

---

## Topic

Building a class hierarchy and using runtime polymorphism. You will implement a
`Shape` abstract base class and three derived shapes (`Circle`, `Rectangle`,
`Square`), then write functions that operate on shapes through base-class
pointers.

## Learning Objectives

By the end of this lab you should be able to:

- Define an **abstract base class** using a **pure virtual function**.
- Use **public inheritance** to model an *is-a* relationship.
- **Override** virtual functions in derived classes (`override` keyword).
- Understand why base classes need a **virtual destructor**.
- Call the correct method at runtime via **dynamic dispatch** through a base
  pointer (`Shape*`).
- Process a heterogeneous collection of objects **polymorphically**.

## Prerequisites

- Classes, constructors, member initializer lists.
- Access specifiers (`public`, `protected`, `private`).
- `std::vector` basics and pointers.

## File Structure

```
.
├── MainProgram.cpp          # YOUR work goes here (student version)
├── test.cpp                 # Catch2 tests (do not edit)
├── catch_amalgamated.hpp    # Catch2 (provided)
├── catch_amalgamated.cpp    # Catch2 (provided)
├── Makefile
├── README.md
├── explain.txt
└── explain.md
```

## How to Compile

```bash
make          # builds ./program from MainProgram.cpp
```

## How to Run

```bash
make run      # or: ./program
```

## How to Test

Run all tests:

```bash
make test
```

Run a single group (for partial credit / focused debugging):

```bash
make test_1   # Circle area        [t1]
make test_2   # Rectangle area     [t2]
make test_3   # Square inheritance [t3]
make test_4   # Virtual dispatch   [t4]
make test_5   # totalArea          [t5]
make test_6   # largestShapeName   [t6]
```

On the Linux autograder you may also run a group directly:

```bash
./test_bin [t1]
```

## Submission Instructions

Submit **only** your completed `MainProgram.cpp`. Do not rename any class,
method, or function — the autograder relies on the exact names and signatures.
Do not add header files or extra source files.

## Common Mistakes

- Forgetting `virtual` on the base destructor → undefined behavior when deleting
  through `Shape*`.
- Omitting `override` and accidentally creating a *new* function instead of
  overriding (signature mismatch, e.g. dropping `const`).
- Trying to instantiate `Shape` directly — it is abstract.
- Returning `0.0` / `""` from `totalArea` / `largestShapeName` without handling
  the non-empty case.
- Forgetting to set `name = "Square"` in the `Square` constructor.

## Academic Integrity

This is an individual assignment. You may discuss concepts with peers, but the
code you submit must be your own. Sharing or copying solutions is a violation of
the course academic-integrity policy.
