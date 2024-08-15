# Passing arguments by value

**Objects vs. Primitive types in Java**: In Java, the rules for what is stored 
in a variable are simple: all object variables store object references while 
primitive type variables store values directly. In Java, assignment is done by 
value, so when you assign a primitive variable's value to another variable, the 
actual value is copied; when it is an object variable, the reference is copied, 
and you thus get two references to the same object.

**Objects and Primitive types  in C++**: In C++, on the other hand, there is no 
such distinction between object and primitive type variables. By default, all 
variables, both primitives and objects, actually hold values, and NOT object 
references. C++, like Java, does assignment by value. However, this means 
that when one object variable is assigned to another, a copy of the entire 
object is made (like calling clone in Java). This behaviour is seen as well 
when one calls a method with parameters. The parameters are assigned by 
value, hence copied. This behavior is illustrated in the code example.

To avoid this copying-the-data behaviour in C++, one can use **references** 
or **pointers**.