.PHONY: all

crawl:
	gcc crawl.c -o crawl.ex

clean:
	rm -f *.ex *.o

# ARCH := $(shell uname -m)

# ifeq ($(ARCH), arm)
#   # Compiler and linker flags for Mac OS M1 (ARM)
#   CC = arm-apple-darwin11-clang
#   LDFLAGS = -L/usr/local/lib/arm
# else
#   # Compiler and linker flags for Linux x86-64
#   CC = gcc
#   LDFLAGS = -L/usr/local/lib/x86_64
# endif

# CC = gcc
# CFLAGS = -Wall -Werror -Wextra -O2

# SOURCES = $(wildcard *.c)
# OBJECTS = $(SOURCES:.c=.o)
# EXECUTABLES = $(SOURCES:.c=)

# all: $(EXECUTABLES)

# $(EXECUTABLES): $(OBJECTS)
# 	-$(CC) $(CFLAGS) $@.o -o $@

# %.o: %.c
# 	-$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(EXECUTABLES) $(OBJECTS)


# This Makefile uses the following variables:

# CC: The C compiler to use (in this case, gcc)
# CFLAGS: Compiler flags to use (in this case, -Wall, -Werror, -Wextra, and -O2)
# SOURCES: A list of all .c files in the current directory (generated using the wildcard function)
# OBJECTS: A list of object files corresponding to the .c files (generated using a pattern rule)
# EXECUTABLES: A list of executable files corresponding to the .c files (generated using a pattern rule)
# The Makefile has three targets: all, clean, and the default target (which builds the executables).

# The all target depends on all of the executables and builds them by linking the corresponding object files.
# The default target (which builds the executables) depends on the object files and builds them by compiling the .c files.
# The clean target removes the executables and object files.
