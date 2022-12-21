.PHONY: all

all: crawl_cwd crawl_full parallel pthreads_mutex exe_dir dict regex array_vector fflush_printline json_single_parser get_str_between

aes:
	gcc aes.c -o aes.ex

json_single_parser:
	gcc json_single_parser.c -o json_single_parser.ex

array_vector:
	gcc array_vector.c -o array_vector.ex

crawl_cwd:
	gcc crawl_cwd.c -o crawl_cwd.ex

fflush_printline:
	gcc fflush_printline.c -o fflush_printline.ex

regex:
	gcc regex.c -o regex.ex

logger-main:
	gcc -o logger-main.ex logger-main.c logger.c

dict:
	gcc dict.c -o dict.ex

crawl_full:
	gcc crawl_full.c -o crawl_full.ex

exe_dir:
	gcc exe_dir.c -o exe_dir.ex

parallel:
	gcc parallel_compute.c -o parallel_compute.ex -lpthread

pthreads_mutex:
	gcc pthreads_mutex.c -o pthreads_mutex.ex -lpthread

prompt:
	gcc prompt.c -o prompt.ex

prompt-safe:
	gcc prompt-safe.c -o prompt-safe.ex

multi_2:
	gcc multi_2_main.c -o multi_2.ex -lpthread

hpc_vectorization:
	gcc hpc_vectorization.c -o hpc_vectorization.ex -lpthread

sockets_http:
	gcc sockets_http.c -o sockets_http.ex

yaml_parse:
	gcc yaml_parse.c -o yaml_parse.ex

get_str_between:
	gcc get_str_between.c -o get_str_between.ex

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
