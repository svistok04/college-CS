# Genericity 

Like Java, the C++ programming language supports generic functions and 
generic classes. In C++, generic functions are called template functions and 
generic classes are called template classes or template functions. The 
motivations are very similar for both languages: how to write several 
classes that share common behaviors and for which you define the behavior 
based on an abstract data type. 

It is probably easier to explain the principle with a simple example. Say 
that you want to create a class that does perform some basic arithmetic 
operations on integers. This is demonstrated in the example program. In this 
example, the `Arithmetic` class explicitly uses integers. 

Assume that we want to do arithmetic with floating point numbers rather than 
with integers. Obviously, one can rewrite the `Arithmetic` class by 
replacing `int` with `float`. This means that we need to rewrite the same 
class by simply changing the type in all member declarations. This is not 
very efficient and sustainable. One needs to duplicate important parts of 
the code, which is also difficult for maintenance. 

C++, like Java, allows to do better with the use of template/generic classes.
This is demonstrated in the next task.