# C++ template functions

The `max()` function usually takes two arguments and returns the argument 
such that this argument is `>` to the other argument.

Given the `max()` function that takes two integer numbers as parameters, 
```
int max(int a, int b) {
    return a >= b ? a : b;
}
```
make this function generic by declaring a template function. As you can 
observe in the `main` program, this template function can be used for any 
type that defines/overloads the `>` operator.