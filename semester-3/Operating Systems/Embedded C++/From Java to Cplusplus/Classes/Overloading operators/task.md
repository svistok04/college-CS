# Overloading operators

In C++, unlike in Java, operators may be overloaded when declaring a class. 
Thus, a programmer can use operators with user-defined classes/types. These 
operators are defined with the keyword `operator` followed by the symbol 
used for the operator being defined. Like any other method, an operator has 
a return type and a parameter list. In other words, C++ operators are 
methods with special names.

Operators that are commonly overloaded in a class are:
- the copy assignment operator defined as `T& operator=(const T& other)`, 
  expected to perform no action on self assignment and to return the lhs of 
  the operation by reference.
- comparison operators such as `bool operator==(const T&, const T&)` for 
  comparing two instances of the class.
- user-defined conversion function written as `operator conversion-type-id` 
  such as `operator int()` for converting an instance of the class to an `int` 
  value.

The program example illustrates the overloading of different operators for a 
class that represents rational numbers. 