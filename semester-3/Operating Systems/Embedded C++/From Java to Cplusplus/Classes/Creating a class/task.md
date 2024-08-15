# Classes in C++

C++ is an object-oriented language and programmers can use existing classes or 
create their own classes in their program. Class creation is very similar to 
class creation in Java. It is also somehow related to `struct` in the C 
programming language. In C, a `struct` is a collection of attributes without 
any object-oriented feature - it has no constructor, no method, and no 
inheritance. A class in C++ is also a collection of attributes, but it also 
implements all object-oriented features. It has a constructor, methods, it can 
inherit from other classes and it allows encapsulation with access keywords.

A simple illustration of this concept is given with the `Point` class, which 
defines a data type representing a point in 2-D space.

Both constructors include a member initialization list, with the : colon 
character followed by a comma-separated list of member initializers. In this 
example, the two class attributes `_x` and `_y` are initialized with either the 
0 value or with the values passed as arguments to the constructor.

Based on the `Point` class example, it is important to note the following 
points:
- A class may define one or several constructors which are called upon object 
  creation. These constructors may have no, one or several parameters and may 
  thus be overloaded - like any class method. Overloaded constructors or methods 
  differ in the number and/or type of parameters.
- One of the constructors is called each time an object is created on the stack 
  or on the heap.
- Unlike Java, access modifiers are defined by section and not individually for 
  each method or data members.
- In C++, accessor (or "getter") methods are tagged with the keyword `const`, 
  which prevents the method from modifying instance variables.
- In C++, there is a semicolon after the class's closing bracket.

More details are given later in this course on the C++ class concept, including 
on inheritance and template classes.