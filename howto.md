To use libraries in your C programs that you compile with a Makefile, you need to download the libraries and install them on your system. There are several ways to do this, depending on the library and your operating system.

Here are some general steps you can follow to download and use libraries in your C programs:

Find the library you want to use. There are many libraries available online that you can use for your C programs. Some popular libraries include libcurl, openssl, zlib, sqlite3, and SDL2.
Check if the library is available in your operating system's package manager. Many libraries are available through package managers such as apt, yum, or brew, which can make it easier to install and manage the library.
Download the library. If the library is not available in your operating system's package manager, you can download it from the library's website or a package repository such as GitHub. Make sure to download the correct version of the library for your system.
Install the library. If you downloaded the library from a package repository, you may need to build and install it manually. This usually involves running ./configure, make, and make install in the library's source directory. If you downloaded a pre-built package, you may need to follow specific instructions for installing the package.
Update your Makefile. After installing the library, you need to update your Makefile to link your program with the library. You can do this by adding the library's name to the LDFLAGS variable, and by specifying the path to the library's header files in the CFLAGS variable. For example, if you are using the json-c library, you can add the following lines to your Makefile:
Copy code
CFLAGS += -I/path/to/json-c/include
LDFLAGS += -L/path/to/json-c/lib -ljson-c
Make sure to replace /path/to/json-c with the actual path to the json-c library on your system.

Include the library's header files in your code. After updating the Makefile, you can include the library's header files in your code by adding a #include directive at the top of your source files. For example, if you are