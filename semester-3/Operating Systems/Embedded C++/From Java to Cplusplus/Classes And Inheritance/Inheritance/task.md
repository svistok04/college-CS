# Inheritance

**Inheritance** in C++ is implemented by adding the list osf inheritances after
the class name followed by a `:`. For making the public members of the base
class accessible as public members of the derived class, the inheritance must be
declared `public`.

Unlike in Java, a class in C++ can inherit from multiple classes (**multiple** 
inheritance vs. **single** inheritance).

Unlike Java, C++ does not distinguish between inheritance and interface 
implementation. In Java, a class can only inherit from one class (using the 
`extends` keyword) but it can implement several interfaces (using the 
`implements` keyword). In C++, both concepts are implemented using inheritance. 
Interfaces are usually declared as classes that contain only **pure virtual 
methods**. Virtual and pure virtual methods are explained in a following task.

In Java, the keyword `super` is used to call the base constructor. In C++, 
base class constructors are automatically called for you if they have no 
argument. To call a superclass constructor with an argument, the 
initialization list must be used. This is illustrated in the `Base2` 
and `Derived` classes.