# Vectors

The C++ `std::vector` class owns the best features of the array and 
ArrayList in Java. A C++ `std::vector` has convenient elemental access (using 
the familiar [] operator) and it can grow dynamically. 

The `std::vector` is a template class (similar to a generic class in Java). 
If `T` is some type, then `vector<T>` is a dynamic array of 
elements of type `T`. More details will be given later regarding template 
classes in C++.

A vector also provides the convenient `push` and `pop` 
functionalities of a stack, where you can add an element to the back of the 
vector using the `push_back()` method, and you can remove the last 
element of the vector using the `pop_back()` method. It's possible to 
access the first element with the `front()` function and the last element 
with the `back()` function.  

For a vector `v`, the valid indices are between `0` and `v.size()-1` (just 
like for arrays or for Java). However, unlike in Java, there is no runtime 
check for legal indices, so accessing an illegal index could cause you to 
access garbage data without even realizing it. In fact, accessing a 
nonexistent element of a vector through the `[]` operator is undefined 
behavior in C++.

For more information about vectors and its methods, check out [this official 
page](https://en.cppreference.com/w/cpp/container/vector).