# User Defined Conversions by Constructor and Conversion Operators

User defined conversions are very useful sometimes. However, they should be 
used with care, because they can also lead to unpredicted conversions and 
errors that may be hard to locate.

## Constructor

When a constructor with parameters is defined in a class, it defines 
conversion that can be used implicitly. If it is not intended to be able to 
convert from this specific type to the type defined by the class, an 
`explicit` keyword should be added in front of the constructor. This is 
demonstrated in the `String` class. Add the `explicit` keyword for defining 
constructors and observe the errors in the `main()` function.

## Conversion operators

Defining conversion operators such as `operator int()` for allowing implicit 
and explicit conversions to the converted type (`int` value in this case) 
must be used with care. Such conversion operators make sense when an 
instance of the class can be represented as a value of the converted type. 
In embedded programming, this applies for instance for an input pin, where 
the `operator int()` conversion operator can be considered as a shortcut to 
a `read()` method that delivers the value read on the input pin. In the 
example program, we demonstrate an example of an `operator int()` conversion 
operator that is probably not as wise.
