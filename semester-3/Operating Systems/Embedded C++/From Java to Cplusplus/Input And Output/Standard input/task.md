# Standard input

As already explained, the standard input is represented by the `std::cin` 
object. The `>>` operator is used to read from the standard input (or any 
_istream_, for that matter).

The `getline()` method reads an entire line of input (from any _istream_).

If the end of input has been reached, or if something could not be read 
correctly, the stream is set to a failed state, which you can test for using 
the `fail()` method.

You may experience this behavior by running the `main` program. If for `n`, you 
input a value on the keyboard that is not an integer value, you may observe 
the error. 