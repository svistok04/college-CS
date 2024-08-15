# Virtual methods

Virtual methods are member methods whose behavior can be overridden in derived 
classes. As opposed to non-virtual methods, the overriding behavior is preserved 
even if there is no compile-time information about the actual type of the class. 
This is illustrated by the `main.cpp` file.

If you run the program snippet, you should observe that the expected methods 
are called. You may then modify this program by removing the `virtual` modifier 
keyword from the `Base` class and the `override` keyword from the `Derived` 
class. You should then observe that in all cases the `f()` method from the 
declared type is called.

Note that the use of the `override` keyword is optional. It is however very 
useful for identifying method redefinition errors at compile time, since it 
indicates to the compiler that a specific method is a method that is redefined 
in the derived class.

Without going to more details, one may say that virtual methods are like any 
non `final` methods in Java. The method that is effectively called is the 
one of the run-time type of the object (and not the one of the declared type)
. From this perspective, polymorphism is existing in both C++ and Java. 
