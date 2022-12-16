# make PLATFORM=Linux ARCH=aarch64
# make clean PLATFORM=Darwin MACHINE=arm64

# Compiler and linker
CC = gcc
LD = ld

# Compiler flags
CFLAGS = -Wall -I/path/to/json-c/include

# Linker flags
LDFLAGS = -L/path/to/json-c/lib -ljson-c -linotify

# Target and source files
TARGET = orchestrate
SOURCES = orchestrate.c

# Platform-specific compiler and linker flags
PLATFORM = $(shell uname -s)
ifeq ($(PLATFORM),Linux)
  ARCH = $(shell uname -m)
  ifeq ($(ARCH),aarch64)
    CFLAGS += -march=armv8-a
  endif
endif
ifeq ($(PLATFORM),Darwin)
  MACHINE = $(shell uname -m)
  ifeq ($(MACHINE),arm64)
    CFLAGS += -march=armv8-a
  endif
endif

# Build target
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Clean target
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
