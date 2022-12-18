By default, gcc searches for header files and libraries in a set of predefined directories. These directories are specified as command line options when the compiler is built, and may vary depending on your system and the version of gcc that you are using.

On most systems, gcc looks for header files in the following directories:

/usr/local/include
/usr/include
gcc also searches for libraries in the following directories:

/usr/local/lib
/usr/lib
You can use the gcc -v command to see the full list of directories that gcc searches for header files and libraries. The directories are listed under the #include <...> search starts here: and #library directories: lines in the output.

## Using compilcated file structures with compiling and linking

To compile and link a source code file support/myfuncs.c that includes a header file include/myfuncs.h into an executable binary using gcc, you can use the -I option followed by the directory where the header file is located, as well as the -L option followed by the directory where the object file will be created.

For example, consider the following directory structure:

```
/project
|-- src/
|   |-- main.c
|
|-- include/
|   |-- myfuncs.h
|
|-- support/
|   |-- myfuncs.c
```
To compile and link the support/myfuncs.c file into an executable binary myprogram that is located in the src directory, you can use the following gcc command:

```
gcc -I/project/include -L/project/support -o src/myprogram src/main.c support/myfuncs.c
```
This command tells the compiler to search the /project/include directory for header files and to create the object file in the /project/support directory when compiling the support/myfuncs.c file. It also tells the linker to link the object file into the src/myprogram executable binary.

Alternatively, you can compile the support/myfuncs.c file into an object file and then link the object file into the executable binary in a separate step. To do this, you can use the -c option to compile the source code file into an object file, and then specify the object file as an argument to the gcc command when linking.

For example:

```
gcc -I/project/include -c -o support/myfuncs.o support/myfuncs.c
gcc -L/project/support -o src/myprogram src/main.c support/myfuncs.o
```
This first command compiles the support/myfuncs.c file into an object file support/myfuncs.o, using the -I option to specify the location of the header file and the -c option to tell the compiler to create an object file instead of an executable binary. The second command links the object file into the src/myprogram executable binary.

## Including header does not mean you're including source or object file
So the functions and structs may be declared in the header file, but the compiler will not know where to find the definitions of these functions and structs unless you also specify the source code file or object file that contains the definitions.

When you use the -I option to specify a directory for the compiler to search for header files, the compiler will only search that directory for header files. It will not search for source code files or object files in that directory.

For example, consider the following directory structure:

```
/project
|-- src/
|   |-- main.c
|
|-- include/
|   |-- myheader.h
|
|-- support/
|   |-- mysource.c
```
In this example, the main.c file in the src directory includes the myheader.h file in the include directory. To compile the main.c file, you can use the following gcc command:

```
gcc -I/project/include src/main.c
```
This command tells the compiler to search the /project/include directory for header files when compiling the src/main.c file. It does not search for source code or object files in the include directory.

If the myheader.h file includes declarations for functions or data structures that are defined in the mysource.c file in the support directory, the compiler will not be able to find the definitions of these functions and data structures unless you also specify the mysource.c file as an argument to the gcc command.

For example:

```
gcc -I/project/include src/main.c support/mysource.c
```
This command tells the compiler to search the /project/include directory for header files and to compile the support/mysource.c file along with the src/main.c file.


## Multiple definitions declared in the main source file,


Yes, you can use different source code files to define functions and data structures that are declared in a header file in C. This can allow you to use different implementations of the functions depending on the target architecture or other factors.

To do this, you can use the #ifdef, #ifndef, and #endif preprocessor directives to conditionally include source code files based on predefined symbols.

For example, consider the following header file includes/myfuncs.h:

```
#ifndef MYFUNCS_H
#define MYFUNCS_H

void foo();


#endif
```
This header file declares a function foo() that is used in other parts of your program.

Now, suppose you have two different source code files that define the foo() function, arm/myfuncs.c and x86/myfuncs.c, which are optimized for the ARM and x86 architectures, respectively.

You can use the following source code file src/main.c to include the appropriate source code file depending on the target architecture:

```
#include "includes/myfuncs.h"

#ifdef ARM
#include "arm/myfuncs.c"
#endif

#ifdef X86
#include "x86/myfuncs.c"
#endif

int main()
{
    foo();
    return 0;
}
```

This source code file includes the includes/myfuncs.h header file, which declares the foo() function. It then uses the #ifdef and #endif preprocessor directives to conditionally include the arm/myfuncs.c or x86/myfuncs.c source code files depending on whether the ARM or X86 symbols are defined.

To compile this source code file, you can use the following gcc command:
```
gcc -DARM src/main.c
```
This command defines the ARM symbol and compiles the src/main.c file. The compiler will include the arm/myfuncs.c source code file when compiling the src/main.c file, and will use the definitions in that file to compile the foo() function.

If you want to compile the source code file for the x86 architecture, you can use the following gcc command:
``` 
gcc -DX86 src/main.c
```
This command defines the X86 symbol and compiles the src/main.c file. The compiler will include the x86/myfuncs.c source code file when compiling the src/main.c file, and will use the definitions in that file to compile the foo() function.

You could also define neither ARM nor X86, in which case the compiler will not include either source code file when compiling the src/main.c file. This will result in a compiler error, since the foo() function is not defined in the src/main.c file.
 
But you can also use the -c option to compile the source code file into an object file, and then specify the object file as an argument to the gcc command when linking.

For example, consider the following source code file src/main.c:

```
#include "includes/myfuncs.h"

int main()
{
    foo();
    return 0;
}
```
To compile this source code file into an object file, you can use the following gcc command:
```
## first compile the arm/myfuncs.c file into an object file, including the header file
gcc -c -Iincludes arm/myfuncs.c -o arm/myfuncs.o

## then compile the src/main.c file and include the arm/myfuncs.o object file
gcc -Iincludes src/main.c arm/myfuncs.o -o main
```

The same thing, but with the x86/myfuncs.c file:
```
gcc -c -Iincludes x86/myfuncs.c -o x86/myfuncs.o
gcc -Iincludes src/main.c x86/myfuncs.o -o main
```


## Using a lib
```
## Specify dir path
gcc myprogram.c -L/path/to/libraries -lmylibrary -o myprogram
## dont specify dir path
gcc myprogram.c -lmylib -o myprogram

## Using headers in a separate dir
gcc -I/path/to/headers myprogram.c -o myprogram
```


To link a shared object (also known as a "dynamic library") with a C program using gcc, you can use the -l option followed by the name of the library, as well as the -L option followed by the directory where the library is located.

For example, consider the following source code file that uses a function foo() defined in a shared object libmylib.so:

```
#include "myheader.h"

int main()
{
    foo();
    return 0;
}
```
To compile and link this source code file with the libmylib.so library, you can use the following command:

```
gcc myprogram.c -L/path/to/libraries -lmylib
```
This tells the compiler to search the /path/to/libraries directory for the libmylib.so library when linking the program, and to include the foo() function in the resulting executable.

The -l option is usually followed by the name of the library without the lib prefix or the .so extension. For example, to link to the libm.so math library, you would use -lm.

You can also include a header file in your source code using the #include directive, as you would with any other header file. The header file should contain the declarations for the functions and data structures that are defined in the shared object.

For example:

Copy code
#include "myheader.h"

int main()
{
    struct data_struct data;
    foo(&data);
    return 0;
}
In this example, the myheader.h file might contain declarations for the data_struct data structure and the foo() function, as well as any other functions or data structures that are used in the program.

^This also applies to .a files


## Compiling .o files and linking them later, vs. compiling straight from .c

In C, it is common to compile source code files into object files and then link the object files together to create an executable binary.

Object files are compiled versions of source code files that contain machine code that can be executed on a specific processor architecture, as well as information about symbols (e.g. function names and variable names) that can be used by the linker. Object files are usually denoted by the .o file extension.

There are several reasons why you might want to compile source code files into object files before linking them into an executable binary:

Modularity: By dividing your source code into multiple source files and compiling them into separate object files, you can organize your code into logical units that can be compiled and tested independently. This can make it easier to maintain and debug your code.
Reusability: Object files can be used as building blocks for multiple executables or libraries. This can save compilation time if you need to build multiple executables or libraries that use common code.
Separation of concerns: Compiling source code files into object files allows you to separate the process of generating machine code from the process of linking the machine code into an executable. This can make it easier to optimize and debug your code.
To compile a source code file into an object file using gcc, you can use the -c option followed by the name of the source file. For example:

```
gcc -c main.c
```
This command compiles the main.c file into an object file main.o.

To link object files into an executable binary using gcc, you can specify the object files as arguments to the gcc command. For example:

```
gcc main.o helper.o -o myprogram
```
This command links the main.o and helper.o object files into an executable binary myprogram.

Alternatively, you can use the gcc command to compile and link source code files into an executable binary in a single step. To do this, you can specify the source code files as arguments to the gcc command instead of object files. For example:

```
gcc main.c helper.c -o myprogram
```
This command compiles the main.c and helper.c source code files into object files and then links them into an executable binary myprogram.


## Using libraries

To use libraries in your C programs that you compile with a Makefile, you need to download the libraries and install them on your system. There are several ways to do this, depending on the library and your operating system.

Here are some general steps you can follow to download and use libraries in your C programs:

Find the library you want to use. There are many libraries available online that you can use for your C programs. Some popular libraries include libcurl, openssl, zlib, sqlite3, and SDL2.
Check if the library is available in your operating system's package manager. Many libraries are available through package managers such as apt, yum, or brew, which can make it easier to install and manage the library.
Download the library. If the library is not available in your operating system's package manager, you can download it from the library's website or a package repository such as GitHub. Make sure to download the correct version of the library for your system.
Install the library. If you downloaded the library from a package repository, you may need to build and install it manually. This usually involves running ./configure, make, and make install in the library's source directory. If you downloaded a pre-built package, you may need to follow specific instructions for installing the package.
Update your Makefile. After installing the library, you need to update your Makefile to link your program with the library. You can do this by adding the library's name to the LDFLAGS variable, and by specifying the path to the library's header files in the CFLAGS variable. For example, if you are using the json-c library, you can add the following lines to your Makefile:
```
CFLAGS += -I/path/to/json-c/include
LDFLAGS += -L/path/to/json-c/lib -ljson-c
```
Make sure to replace /path/to/json-c with the actual path to the json-c library on your system.

Include the library's header files in your code. After updating the Makefile, you can include the library's header files in your code by adding a #include directive at the top of your source files. For example, if you are
