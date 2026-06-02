# Inheritance and Polymorphism

## 1. Concept Overview

**Inheritance** lets one class (the *derived* class) reuse and extend the
members of another (the *base* class). It models an **is-a** relationship: a
`Circle` *is a* `Shape`. With `class Circle : public Shape`, every `Circle`
automatically has the public interface of `Shape`.

**Polymorphism** ("many forms") lets you treat objects of different derived
classes uniformly through a base-class pointer or reference, while still
executing each object's own version of a function. In C++ this runtime behavior
is enabled by **virtual functions** and resolved by **dynamic dispatch** (the
correct override is chosen at run time, based on the real object).

## 2. Key Concepts

- A **base class** defines a common interface; **derived classes** specialize it.
- A **virtual function** can be overridden by derived classes.
- A **pure virtual function** (`= 0`) has no base implementation and makes the
  class **abstract** — it cannot be instantiated, only inherited from.
- **Public inheritance** preserves the *is-a* relationship and keeps the base's
  public interface public.
- A base class used polymorphically needs a **virtual destructor** so that
  `delete basePtr;` runs the correct derived destructor.
- Inheritance can be **chained**: `Square : Rectangle : Shape`.

## 3. Important Keywords

- **`virtual`** — marks a function as overridable; enables dynamic dispatch.
- **`= 0` (pure virtual)** — no implementation in the base; forces derived
  classes to provide one; makes the class abstract.
- **`override`** — declares intent to override a base virtual; the compiler
  errors if no matching base function exists (catches typos / `const`
  mismatches).
- **`public` (inheritance)** — `class D : public B` keeps the *is-a*
  relationship and base's public members public.
- **`protected`** — accessible in the class and its derived classes, but not
  outside.
- **Base pointer (`Base*`)** — a single pointer type that can point to any
  derived object; the vehicle for polymorphism.

## 4. Common Mistakes

- Forgetting `virtual` on the base function → the base version is called even
  through a derived object (static binding bug).
- Forgetting a **virtual destructor** → deleting via `Base*` leaks or corrupts.
- Signature mismatch when "overriding" (e.g. dropping `const`) → creates a new,
  unrelated function instead of an override. Use `override` to catch this.
- Trying to instantiate an abstract class (`Shape s;`) → compile error.
- Re-implementing a function in a derived class that could simply be inherited
  (e.g. `Square` reusing `Rectangle::area`).

## 5. Mini Examples

Abstract base + override:

```cpp
class Shape {
public:
    virtual ~Shape() {}
    virtual double area() const = 0;     // pure virtual -> abstract
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w_, double h_) : w(w_), h(h_) {}
    double area() const override { return w * h; }
};
```

Dynamic dispatch through a base pointer:

```cpp
Shape* s = new Rectangle(3, 4);
double a = s->area();   // 12 -> Rectangle::area() chosen at run time
delete s;               // virtual dtor -> correct cleanup
```

Processing a collection polymorphically:

```cpp
double totalArea(const std::vector<Shape*>& v) {
    double sum = 0;
    for (const Shape* s : v) sum += s->area();  // each calls its own area()
    return sum;
}
```

## 6. When to Use This

- You have several types that share a common interface but behave differently
  (shapes, file formats, payment methods, game entities).
- You want to store mixed types in one container and operate on them uniformly.
- You want to add new types later **without** rewriting the code that uses the
  base interface (open/closed design).
- Avoid it when there is no genuine *is-a* relationship — prefer **composition**
  ("has-a") in that case.
