# Passing arguments by pointer

Pointers in C++ are actually quite similar to references in Java. They are 
variables that store the memory address of some data, as opposed to storing the 
data directly. That is, their value is a memory address. A major difference 
is that in C++, a pointer merely stores the address of the object and it 
does contain any mechanism for counting references to the object.

If `T` is some type, then `T*` is the syntax to declare a pointer to a `T` 
variable. A pointer variable can be initialized either with `std::nullptr`, 
with the value of another pointer variable, with the memory address of 
another variable, or with a call to `new`. The memory address of a variable 
can be attained by placing the `&` symbol before the variable name. To 
access the object to which a pointer points to, you must "dereference" the 
pointer by placing the `*` symbol before the variable name. To access an 
instance variable of the object to which a pointer points, you can use the 
`->` operator on the pointer. These different scenarios are illustrated in 
the code example.