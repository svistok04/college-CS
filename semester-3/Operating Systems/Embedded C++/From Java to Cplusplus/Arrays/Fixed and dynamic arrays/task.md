# Fixed and dynamic arrays

In most object-oriented programming languages like Java or C++, the programmer 
may create and use arrays. As for objects, there are some differences in the way 
arrays may be created. In C++, we may distinguish between arrays of fixed or 
dynamic size:  
- Arrays of fixed size are arrays for which the size is known at compile time.
- Arrays of dynamic size are arrays for which the size is not known at 
  compile time and can be computed by the program (possible since C99/C++99).

The code snippet demonstrates the creation and usage of arrays. Observe how 
arrays are created on the stack or on the heap as explained below. As you 
will see, in C++ unlike in Java, complex objects like arrays can be 
allocated on the stack as well. 

For an array `a`, the valid indices are between `0` and `a.size()-1` 
(just like for Java). However, unlike in Java, there is no runtime
check for legal indices, so accessing an illegal index could cause you to
access garbage data without even realizing it. It could also cause crashes.

