# Use `std::cin`

The purpose of the program snippet is to compute the sum from `0` to the 
number given by the user. For example, entering `5` would give `5 + 4 + 3 + 
2 + 1 + 0 = 15`.
You must implement the following steps:
- Firstly, get the user input. 
- Secondly, the `stoi()` method interprets a signed integer value in the 
  given string or raises an exception. 
- Thirdly, the result is displayed.

Complete the program snippet so that it runs without error. There are three 
cases to verify : 
- Any number entered gives the sum. For example, entering 5 displays 15.
- Any letters entered raises the invalid argument exception, displaying an 
  error message (in red).
- Any number bigger than int (ex : 12345678901) raises the out of range 
  exception, displaying an error message (in red).

You may run the program using the "Run" command.