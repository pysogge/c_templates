# Tool Scripts

# Script fo remove "orchestration_" prefix from all files in directory
# Usage: remove_prefix <directory>
remove_prefix() {
    for file in $1/*; do
        mv $file ${file/orchestration_/}
    done
}

# Script for remove "_1" suffix from all files in directory, maintaining the .c and .h file extensions
# Usage: remove_suffix <directory>
remove_suffix() {
    for file in $1/*; do
        mv $file ${file/_1/}
    done
}

## Script to generate a Makefile that compiles all .c files in a directory
## Usage: generate_makefile <directory>
generate_makefile() {
    echo "CC = gcc" > $1/Makefile
    echo "CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99" >> $1/Makefile
    echo "SRC = \$(wildcard *.c)" >> $1/Makefile
    echo "OBJ = \$(SRC:.c=.o)" >> $1/Makefile
    echo "all: \$(OBJ)" >> $1/Makefile
    echo "\$(OBJ): \$(SRC)" >> $1/Makefile
    echo "	\$(CC) \$(CFLAGS) -c \$(SRC)" >> $1/Makefile
    echo "clean:" >> $1/Makefile
    echo "	rm -f \$(OBJ)" >> $1/Makefile
}