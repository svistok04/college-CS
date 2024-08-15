# Constants 

In C, constants are often defined using the `#define` primitive. With this 
primitive, the pre-processor first textually replaces all defined symbols in 
the code, before the compiler does perform its job. Using such primitives 
has many drawbacks and with C++, constants should be defined using the 
`const` or `constexpr` keyword. 

Both keywords are often combined with the `static` keyword. Constants can be 
defined globally or within a class scope as demonstrated by the 
`class_with_constant.hpp` file.