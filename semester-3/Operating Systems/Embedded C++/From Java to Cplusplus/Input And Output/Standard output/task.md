# Standard output

In C++, the standard output, standard input, and standard error streams are 
represented by the `std::cout`, `std::cin`, and `std::cerr` objects, 
respectively. Also, newline characters can be outputted using the `std::endl` 
keyword. You use the `<<` operator to write to standard output (or to any 
_ostream_, for that matter). 

## Standard output/input in embedded systems

Embedded systems often offer different ways of logging information on the 
console. For this reason, embedded programs do not use mechanisms such as 
`std::cout` or `std::cin` for standard output or input, but they rather use 
dedicated libraries.

