# Header and source files

- In C++, the code can be split between a `.cpp` file (known as source file)
  and a `.hpp` file (known as header file). The constructors and methods are
  declared in the `.hpp` file but the actual implementations are listed in the
  `.cpp` file.
- In the `.cpp` file, each constructor or method definition is preceded by the
  name of the class followed by `::` (e.g. void `LED::toggle()`).

Here, the `Point` class is separated in the two corresponding files. The 
'main.cpp' must then import the `Point.h` file to access the public methods 
and variables.