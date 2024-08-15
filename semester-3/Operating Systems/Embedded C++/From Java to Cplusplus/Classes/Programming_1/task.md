# Writing a C++ class

The `Student` class must be completed. The `main()` method should run without 
errors and produce the expected results.

Observe the following points for the `Student` class : 
- It has a first_name (`std::string`), a last_name (`std::string`) and an 
  age (`int`) as attributes.
- It has a constructor without parameters that initialize the student to the 
  following values ; "Toto" (first_name), "Titi" (last_name) and 18 (age).
- It has another constructor with the first name, last name and age as 
  parameters. It initializes a `Student` instance to the given parameters.
- The public method `isMajor()` returns `true` if the age is bigger or equal 
  to 18, `false` otherwise.
- The public method `name()` returns the concatenation of the first name 
  and the last name with a space in between. 