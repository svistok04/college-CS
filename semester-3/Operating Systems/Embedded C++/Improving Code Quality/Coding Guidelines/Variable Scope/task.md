# Variable scope and initialization 

## Minimize global and shared data

This includes the following statements:

- Avoid data with external linkage, because it creates coupling between 
  different parts, potentially distant, of the programs.
- Names of variables in the global namespace pollute this namespace.
- Order of initialization of variables in different compilation units is 
  difficult to understand and handle.
- In any case, access to global shared data needs to be serialized.
- A declaration of a name in a block can hide a declaration in an enclosing 
  block or a global name. Hiding names are difficult to discover for 
  programmers. 

## Declare variables as locally as possible

As a generic rule, variables represent a state and this state lifetime should 
be as short as possible. If a variable lives longer than expected, then

- it makes the program harder to understand and maintain.
- it pollutes its context with its name, meaning that its name exists in a 
  context where it has no meaning.
- it can't always be initialized with a meaningful value. You should not 
  declare a variable that you cannot initialize sensibly.

Remember that the requirement of older versions of C where variables must be 
declared only at the beginning of a scope is obsolete in C++. 

## Always initialize a variable

Uninitialized variables are an important source of bugs in C and C++ programs.
This includes:
- cleaning memory before using it.
- initialize variables upon declaration.

Recall that the compiler is not required to initialize variables unless the 
program does it explicitly. Local variables or class attributes forgotten 
from the constructor initializer list may thus be not initialized before they 
are used.