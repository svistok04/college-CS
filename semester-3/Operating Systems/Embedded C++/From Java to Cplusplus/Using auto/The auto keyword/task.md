# The `auto` keyword

## What is the `auto` keyword
C++ is a strongly typed language and the type of each variable must be known 
at compile time. Before _C++11_, the programmer had to specify the type of 
each variable when declaring the variable. However, since _C++11_, when 
declaring a variable, the programmer does not need to state its type 
**_explicitly_**, when it can be deduced from its initializer. Some examples 
where `auto` can be used are shown below:

```C++
auto b = true; // b is a boolean
auto ch = 's'; // ch is a char
auto i = 1234; // i is an int
auto l = 1234L; // l is a long
```

## When should a programmer use `auto`

In general, `auto` should or could be used when there isn't a specific 
reason to mention the type explicitly. Reasons for specificying the type 
explicitly are:

- Readibility: when the type of a variable or the type returned by a 
  function must be clearly visible to users of the variable or function.
- When the range of a variable must be made explicit, like between a `float` 
  or `double` variable.

## Advantages of using `auto`

The use of `auto` provides the following advantages:

- It avoids redundancy.
- It avoids writing long type names, which is particularly true when using 
  `template` classes.

Although using `auto` is helpful, it should not be an easy way out for
programmers. Good programmers should understand how `auto` works and what 
types are inferred by the compiler.


