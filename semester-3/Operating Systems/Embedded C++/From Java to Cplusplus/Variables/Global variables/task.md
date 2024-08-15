# Global variables

In C++, as in C, it is possible to allocate global variables. These variables 
are declared outside any function or method scope and are accessible in any 
function or method. It is possible to restrict the scope of a global variable 
to the .c/.cpp file in which it is declared by adding the `static` keyword to 
the variable declaration such as in `static int counter`. Global variables are 
allocated for the entire lifetime of the program in which it is declared. 
They are located in a global memory space.

It is a good practice to limit the use of global variables as much as possible. 
If feasible, prevent their use and limit their scope with the use of the 
`static` keyword.