# Function and method arguments

In C++, like in most object-oriented programming languages, the declaration of 
a method or a constructor declares the number and the type of the parameters 
for that method or constructor. 

Usually, the term parameters refers to the list of variables in a method 
declaration, while the term arguments refers to the actual values that are 
passed in when the method is invoked. When you invoke a method, the 
arguments used must match the declaration’s parameters in type and order.

In Java, all method primitive or reference type arguments are passed by copy. 
This means that any changes to the values of the parameters exist only within 
the scope of the method. More specifically, for reference type arguments this 
means that when the method returns, the passed-in reference still references 
the same object as before.

In C++, arguments can be passed by copy (value), by reference or by address 
(pointer). Passing a argument by reference does not have the same meaning as in 
Java. We present these three possibilities more in more details in the 
following tasks.