# The preprocessor directives

## `#include`
```
#include <file>
#include "file"
```
**Functionality** : The specified file is inserted into the code at the 
location of the directive. Using <> means that the file is provided by the 
implementation (standard libraries), using "" means that the file will be 
searched based on include paths provided to the preprocessor.

**Common use** : Almost always used to include header files so that code can 
make use of functionality that is defined elsewhere.

## `#define`
```
#define key value
```
**Functionality** : Every occurrence of the specified key is replaced with the 
specified value.

**Common use** : Often used in C to define a constant value or a macro. C++ also
provides other mechanisms for constants. Macros must be used very carefully.

## `#ifdef`
```
#ifdef [key]
#ifndef [key]
#if defined(key)
#else
#elif [key]
#elif defined(key)
#endif

#if <value>
#elif <value>
#else
#endif
```
**Functionality** : Code within the #ifdef ("if defined") or #ifndef ("if not 
defined") blocks are conditionally included or omitted based on whether the 
specified value has been defined with #define. <value> can be an expression 
using keys and evaluating to a boolean.

**Common use** : Used for differentiating among different configurations. 
Also used to protect against circular includes.

## `#pragma`
```
#pragma
```
**Functionality** : Varies from compiler to compiler. Often allows the 
programmer to display a warning or error if the directive is reached during 
preprocessing.

**Common use** : Platform specific.

## Example

For a better understanding of what preprocessor, let us look at a simple 
example. We define a header file named `definitions.h` which contains a 
single definition of the key `TABLE_SIZE`. We include this header file in our 
`main.cpp` file - the file that defines the main function executed at program 
launch - and use the `TABLE_SIZE` to define the `main.cpp` behaviour. In 
this case, the preprocessor will transform the `main.cpp` file as:
```
int table[1024];

int main() {
    for (int i = 0; i < 1024; i++) {
        table[i] = i;
    }
}
```

