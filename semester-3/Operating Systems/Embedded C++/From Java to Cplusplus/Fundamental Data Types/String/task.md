# Strings

In C, a string is nothing else than a character array (i.e. `char[]`), 
terminated by the `0` value. In C++, the standard library includes a 
`std::string` type, with similar functionalities as the `String` class of Java.
An important difference as compared to Java is that instances of the string 
class in C++ are not immutable and can thus be modified. Also, since 
overloading operators is possible in C++, the `==` operator has been defined 
for the string class, hence the in-depth comparison of two string instances is 
possible by using the `==` operator. Finally, in C++ string objects can only 
be concatenated with other string objects - no auto-boxing and implicit 
conversions like in Java. 