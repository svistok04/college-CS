# The delete keyword

As already mentioned, an important difference between Java and C++ is the 
concept of releasing an object and its destruction. 

In Java, the Garbage collector is responsible for releasing memory. This 
means that programmers may not explicitely deallocate objects. Programmers 
may define a `finalize()` method for each class, which will be called by the Garbage 
collector upon releasing the object. 

In C++, the programmer must explicitly call the `delete` operator. Upon 
calling `delete`, the destructor of the object class will be called.

The `delete` keyword must be used whenever the `new` keyword is used and the 
object is created on the heap because the memory management is left to the 
programmer's care. When an object is allocated as an array with `new int[2]` 
for instance, then the programmer must deallocate the object with the 
`delete []` statement.