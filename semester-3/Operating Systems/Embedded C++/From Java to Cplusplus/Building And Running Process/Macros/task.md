# The macros

An important point is that a programmer should never forget what the 
preprocessor does: it textually replaces the symbol in the source file
before it is compiled. This practice is still used for C++ programming, but 
because using preprocessor directives may lead to unexpected errors, it 
tends  to be replaced by more robust and modern patterns. For demonstrating 
some potential problems, let us look at the exercise presented by the `main.cpp` file. 

If you answer to the questions asked in the `main()` function, it becomes 
obvious that, in C++, one should rather use inline functions rather than 
macros for defining functions. Also, defining constants using `static 
constexpr` should be preferred to using `#define` macros.