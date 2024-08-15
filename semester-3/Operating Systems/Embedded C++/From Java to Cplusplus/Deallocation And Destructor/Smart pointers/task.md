# Smart pointers and memory deallocation

It is cumbersome and error prone for the programmer to make sure that all 
possible paths within a given scope will release memory. In C++, heap memory 
management can be improved by using object oriented mechanisms. This is 
accomplished by encapsulating memory allocation within classes, so that 
memory is released upon object destruction. This way of doing is often 
called smart pointers (instead of raw pointers). 

It is important to point out that support for smart pointers is implemented 
as part of the C++ standard using the 
[std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr) or
the [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr) 
classes.

Also, be aware that the problem of circular references or cyclic dependency may 
still arise when using the `std::shared_ptr` mechanism.        