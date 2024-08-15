# Object creation on the stack or on the heap

In C++, we can choose if the object is created on the stack (without the 
`new` keyword) or on the heap with the `new` keyword.

When an object is on the stack, it exists until the scope (of the method or 
function) is left. When an object is on the heap, it exists until the 
`delete` keyword.