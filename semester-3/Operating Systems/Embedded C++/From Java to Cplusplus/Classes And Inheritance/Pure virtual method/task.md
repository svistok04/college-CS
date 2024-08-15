# Pure virtual methods

A pure virtual method is a virtual method that has the following syntax: 
`virtual method_declaration = 0;`. A pure virtual method cannot have any 
definition (so it does not have a body).

An abstract class is a class that either defines or inherits one or more pure 
virtual methods. Abstract classes cannot be instantiated - no object of an 
abstract class can be created.

This mechanism is often used in C++ for defining classes that act as interfaces. 
Such classes are similar to interfaces in Java and are used for representing 
concepts in a way that is separated from implementation of the concept. Using 
abstract classes is always through reference or pointer - since no instantiation 
of an abstract class is possible. An instance of a class that inherits from an 
abstract class can be casted to the abstract class reference or pointer. This 
is also illustrated in the given program snippet.