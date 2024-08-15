# Conversions in C

C is relatively permissive in the way values can be converted from one type 
to another one, using the C type cast operator `(type)`.  As demonstrated in 
the example program, many implausible casts are accepted in C and this may 
result in unexpected results. Although the example is using classes, the 
same problem arises with `struct`. 

# Conversions in C++
For making conversions more robust and better documented, C++ introduced 
several type cast operators:
```
static_cast
dynamic_cast
const_cast
reinterpret_cast
```
Each cast operator can be used for a specific purpose and using it documents 
the intended reason for the conversion and it gives the compiler a chance to 
check that the conversion is acceptable.

## `static_cast`

The syntax for using the `static_cast` operator is

`static_cast<type-name>(expression)`

The conversion is valid only if `type-name` can be converted implicitly to 
the same type that `expression` has, or vice-versa. In our example program, 
you can observe that `static_cast` prevents conversion between unrelated 
types, while C-type casts allow them. It does not however protect against 
conversion errors between related types.

More generally, `static_cast` should also be avoided and class hierarchy 
should be designed for avoiding downcasting. While upcasting is safe, 
downcasting may lead to unexpected errors and should be avoided by a proper 
class design. If one needs to access methods from a specialized class, it 
probably means that the class design is not appropriate.

## `dynamic_cast`

`dynamic_cast` is part of the _Runtime type identification_ (_RTTI_) 
mechanism introduced in C++. The goal of _RTTI_ is to provide a standard way 
to determine the type of objects during runtime. The `dynamic_cast` operator 
generates a pointer to a derived type from a pointer to a base type, if this 
conversion is possible. When the conversion is not possible, the operator 
returns `nullptr`. Note that _RTTI_ works only for classes that have 
`virtual` functions.

## Conclusion
_RTTI_ requires additional memory footprint and has an associated cost at 
runtime. Also, in general, compile-time errors must be preferred to run-time 
errors. This means that the programmer should favour robust static 
checks. For this reason, _RTTI_ is not enabled in many embedded development 
frameworks.

As a conclusion, one should avoid upcasting and use `static_cast` rather 
than C-type casts whenever a conversion is required.