# Primitive data types

This section presents the primitive data types of C++.

## Signed data types

Signed integer data types are defined with the `long`, `int`, and `short` 
keywords (no `byte` keyword). However, unlike in Java, the size of each 
integer data types is not defined by the standard - the standard only defines 
the minimum size. 

To specify a size, which is a good practice in Embedded Programming, it is 
recommended to use integer data types with length modifiers such as `int8_t`, 
`int16_t`, `int32_t` or `int64_t`. When using such integer data types, the size 
is not platform specific anymore and portability is improved.

## Unsigned data type

Unlike _Java_, integer values can also be unsigned (only positive) in C/C++.
Unsigned integer data types can be defined by prefixing the integer data types 
with a `u`, such as in `uint8_t`. 

When using unsigned integer data types, 
the programmer must be careful when performing conversion to or from signed data 
types. Conversion operations will always perform without errors and since the 
available ranges differ between signed and unsigned data types, it is the 
responsibility of the programmer to guarantee that no error happens.

## Floating data type

Floating point data types are defined with the `float` and `double` keyword. 
`float` and `double` correspond to single and double precision floating-point 
types, as defined in the [IEEE-754 binary32](https://en.wikipedia.org/wiki/Single-precision_floating-point_format)
format and [IEEE-754 binary64](https://en.wikipedia.org/wiki/Double-precision_floating-point_format) 
format specifications. Their sizes are thus defined by the language, unlike 
integer data types.

## Boolean data type

Boolean type is defined with the `bool` keyword, which may hold the `true` or 
`false` literal values. Note that the size of a boolean variable is also 
platform specific and not necessary 1 byte.

## Character data type

Character data types are usually defined with the `char` keyword. In C++, 
character data types can also be signed and can also be suffixed with a length 
modifier, such as `char8_t` or `char16_t` used for representing UTF-8 or UTF-16 
characters.