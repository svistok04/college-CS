# The header include guards

Typically, C++ header files also make use of preprocessor definitions to make 
sure that they are only included a single time. For this purpose, each header 
file defines a unique symbol and will skip its content if the symbol is already 
defined like shown below:
```
#pragma once

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#define TABLE_SIZE 2048

#endif // _DEFINITIONS_H
```
The `#pragma once` directive can be used for the same purpose. It is supported by 
most toolchains.