# Passing arguments by reference

C++ references are NOT the same as Java references. Although they are related, 
how they are used and their syntax is pretty different, so it is best if you 
simply think of them as different concepts.

References in C++ are simply aliases for existing variables. When you define a 
reference variable in C++, the variable is treated exactly as another name as 
the variable you set it to. Thus, when you modify the reference variable, you 
modify the original variable as well without needing to do anything special.

The syntax for creating a reference variable in C++ is to place an `&` after the 
type name in the variable declaration. If `T` is some type, then `T&` is the 
syntax to declare a reference to a `T` variable.

There are two main uses for C++ references: parameter passing and aliasing long 
variable names. In many cases, it's extremely useful not to make copies of 
objects when they are passed to functions, either because you want the function 
to be able to modify the data in the object, or because you want to avoid 
wasting time and space with the copy.

**Note** : Function or method overloading is possible in C++. Overloading means 
that several methods or functions can have the same name but have different 
parameters (order or types). It is also important to note that since a method 
with the same parameter type passed by value or reference is invoked in the same 
way, it is not possible to overload functions or methods in this case. This is 
the reason why the function addOne() that takes one int parameter as a value 
must have a different name (addOne_val() here) as the `addOne() function that 
takes one int parameter as reference.