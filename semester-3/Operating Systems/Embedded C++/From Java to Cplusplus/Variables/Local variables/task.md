# Local variables

In C++, local variables can be declared and used in functions or methods, as in 
C or Java.

In Java, local variables are allocated on the stack for primitive types 
(e.g. `int` or `float`) and on the heap for reference types (e.g. object of any 
class). This is illustrated in the example below:
```
// declares an initialized reference to a Point object on the heap
Point p1; 
// creates a new Point object and stores a reference to this object in p2
Point p2 = new Point(); 
...
// p3 stores another reference to the object referenced by p2,
// thus p3 and p2 reference the same object
Point p3 = p2;
```
This is a major difference as compared to C++, in which objects can be allocated 
both on the stack (without the `new` keyword) and on the heap (with the 
`new` keyword).

## Allocation on the stack or on the heap

The **stack** is a special area of the memory which stores temporary
variables. In the stack, variables are declared, stored and initialized
during runtime. When the computing task is complete, the memory of the
variable is automatically erased.

The **heap** is a pre-reserved area of computer memory. A program process can
allocate a variable amount of memory from the heap and this memory has to be
differentiated from the stack, data and bss section. On embedded systems,
the heap is very limited in size. It is thus particularly important to monitor
memory allocation on the heap so that NO out of memory error may ever occur.
Whenever possible, it is even better NOT to use the heap and dynamically
allocated memory.

In C++, no garbage collector exists since objects may own raw pointers to the
memory heap. It is thus the programmer’s responsibility to free unneeded heap
space and to call `delete` for each call to `new`. It is a good practice to
reset the pointer value of a deallocated object to `nullptr`.

A **memory leak** is created when memory allocations are managed in such a way
that memory which is NO longer needed is NOT released.