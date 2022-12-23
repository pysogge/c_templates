.PHONY: all

all: crawl_cwd crawl_full parallel pthreads_mutex exe_dir dict regex array_vector fflush_printline json_single_parser get_str_between random_filename args_list time_string dict_d dict_do new_string mkdir is_connected is_connected_any get_ips get_ifaces create_validate_dirs remove_dirs remove_all_files_in_dir async_fork_signal create_validate_dir is_filepath mkdir_p mv_link

aes:
	gcc aes.c -o aes.ex

args_list:
	gcc args_list.c -o args_list.ex

mv_link:
	gcc mv_link.c -o mv_link.ex

mkdir_p:
	gcc mkdir_p.c -o mkdir_p.ex

mkdir_recur:
	gcc mkdir_recur.c -o mkdir_recur.ex

is_filepath:
	gcc is_filepath.c -o is_filepath.ex

async_fork_signal:
	gcc async_fork_signal.c -o async_fork_signal.ex

remove_all_files_in_dir:
	gcc remove_all_files_in_dir.c -o remove_all_files_in_dir.ex

remove_dirs:
	gcc remove_dirs.c -o remove_dirs.ex

create_validate_dir:
	gcc create_validate_dir.c -o create_validate_dir.ex

create_validate_dirs:
	gcc create_validate_dirs.c -o create_validate_dirs.ex

get_ifaces:
	gcc get_ifaces.c -o get_ifaces.ex

get_ips:
	gcc get_ips.c -o get_ips.ex

is_connected:
	gcc is_connected.c -o is_connected.ex

is_connected_any:
	gcc is_connected_any.c -o is_connected_any.ex

mkdir:
	gcc mkdir.c -o mkdir.ex

new_string:
	gcc new_string.c -o new_string.ex

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

time_string:
	gcc time_string.c -o time_string.ex

random_filename:
	gcc random_filename.c -o random_filename.ex

logger-main:
	gcc -o logger-main.ex logger-main.c logger.c

dict:
	gcc dict.c -o dict.ex

dict_d:
	gcc dict_d.c -o dict_d.ex

dict_do:
	gcc dict_do.c -o dict_do.ex

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
