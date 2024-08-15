# The destructor of a class

Upon calling `delete`, the destructor of the object class will be called. The 
concept of a class destructor is illustrated in the updated `Point` class. 
In this example, the destructor doesn't have meaningful statements, but a 
destructor can contain instructions like the constructor does.

- Unlike a constructor, a destructor does not take any argument. So a 
  destructor cannot be overloaded. There may be several constructors for a 
  class, but there may be only a single destructor.
- Like a constructor, a destructor does not return any value.

The destructor is called whenever an object’s lifetime ends, which includes in 
particular:
- The use of the `delete` expression, for objects with dynamic storage duration.
- End of scope, for objects allocated on the stack.

In the `main()` function of the program example, the destructor is first called 
upon the `delete` keyword, then after the program ends because `p1` is at 
the end of the scope.   