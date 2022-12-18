# Create .a static libraries

To release your C program as a library, you will typically need to provide a static library file (denoted by the .a file extension) as well as the header files that declare the functions and data structures that are available in the library.

A static library is a collection of object files that are combined into a single file. When you include a static library in your program, the object files in the library are combined with the object files for your program, and the resulting executable contains all of the code for the library as well as your program.

To create a static library from your C program, you can use the ar tool to combine the object files for your program into a single .a file. For example:

```
ar rcs libmylib.a myfuncs.o myotherfuncs.o
```
This command creates a static library libmylib.a that contains the myfuncs.o and myotherfuncs.o object files.

To use the static library in another C program, you can include the header files that declare the functions and data structures that are available in the library, and then specify the static library as an argument to the gcc command when linking the program.

For example:

```
gcc myprogram.c -L/path/to/libraries -lmylib
```
This command tells the compiler to search the /path/to/libraries


## Create .so dynamic libraries

To create a dynamic library in the .so format (also known as a shared object) from a C program, you can use the gcc compiler with the -shared option and the -o option to specify the name of the output file.

For example, consider the following source code files myfuncs.c and myheader.h:

```
// myfuncs.c
#include "myheader.h"

void foo()
{
    // implementation of foo() function
}
```

```
// myheader.h
void foo();
```
To create a dynamic library libmylib.so from these files, you can use the following gcc command:

```
gcc -shared -o libmylib.so myfuncs.c
```
This command tells the compiler to create a dynamic library libmylib.so that contains the foo() function, which is declared in the myheader.h header file and defined in the myfuncs.c source code file.

To use the dynamic library in another C program, you can include the myheader.h header file in your source code and specify the dynamic library as an argument to the gcc command when linking the program.

For example:

```
gcc myprogram.c -L/path/to/libraries -lmylib
```
This command tells the compiler to search the /path/to/libraries directory for the libmylib.so dynamic library when linking the myprogram.c file, and to include the foo() function in the resulting executable.