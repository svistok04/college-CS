# Template class definition

In the program example, we demonstrate how the `Arithmetic` class defined in 
the previous task can be defined as a generic/template class.

As you can read in the example, the basic syntax for declaring a template
class is as follows:
```
template <class a_type> class a_class {...};
```

In this notation, the identifier `a_type` stands for a data type. Note that 
`a_type` is not a keyword; it is an identifier that during the compilation 
of the program represents a single data type. When the program defines which 
datatype `a_type` is, then a particular instance of `a_class` is 
instantiated, in which `a_type` is of the type declared. In the examples 
given in the program, `a_type` is declared to be `int` or `float`, thus 
creating two instantiations of the template class `a_class`. 

When defining a method as a member of a template class, it must be defined 
as a template method with the following syntax:  

```
template<class a_type> void a_class<a_type>::method() {...}
```
As you can see, to understand template classes, just think about replacing 
the identifier `a_type` everywhere it appears, except as part of the template 
class definition. It is important to note that `a_type` can be any data type, 
including data types defined by your own classes.

Besides the template arguments that are preceded by the class or typename 
keywords, which represent types, templates can also have regular typed 
parameters, similar to those found in methods. As an example, we may 
consider a `Queue` class that is used to contain `queue_sz` 
elements of the type `T`. Such a class is defined as:    
```
template<typename T, uint32_t queue_sz> class Queue {...};
```
This definition allows for instance to allocate arrays of fixed sizes (known 
at compilation) in the definition of the class, such as `T array_in_class
[queue_sz];`.  This type of construction is particularly useful in embedded 
software for allocating the required memory at compile time without using `new` 
operators. The example program illustrates this use.