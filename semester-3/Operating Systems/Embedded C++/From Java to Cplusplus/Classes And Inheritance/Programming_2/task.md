# Classes with pure virtual methods (interfaces)

In the code example, two interfaces are defined (as classes containing only 
pure virtual methods):
- `Printable` : It has the `print()` method.
- `Switch` : It has the `turnOff()` and `turnOn()` methods.

The base class `Led` represents a LED with a given intensity. It implements 
the two interfaces explained above so that it's able to turn off and on, as 
well as print its current intensity.

You must complete the code so that the `main()` function runs without 
errors and produces the expected results. 