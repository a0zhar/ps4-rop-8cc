# Compiler and flags
CFLAGS  := -Wall -Wno-strict-aliasing -std=gnu11 -g -I. -O0
ECC     := ./8cc

# Directory for object files
OBJ_DIR := ./build

# Ensure the object directory exists before building
mkdir_obj_dir := $(shell mkdir -p $(OBJ_DIR))

# Automatically find all .c files and generate corresponding .o file paths
SRCS     := $(wildcard *.c) 
OBJS     := $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter-out main.c,$(SRCS)))
MAIN_OBJ := $(OBJ_DIR)/main.o  # Separate variable for main.o

# Include specific header file
override CFLAGS += -DBUILD_DIR='"$(shell pwd)"'

# Target for creating the executable
8cc: 8cc.h $(OBJS) $(MAIN_OBJ)
	@echo "Linking main.o and object files to create 8cc"
	@cc -o $@ $(OBJS) $(MAIN_OBJ) $(LDFLAGS) 

# Compile source files into object files in the build directory
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compiling $< into $@"
	@cc $(CFLAGS) -o $@ -c $<

# Ensure the object directory exists before building
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean up artifacts
clean: cleanobj
	@echo "Cleaning up build artifacts"
	@rm -f 8cc stage?

cleanobj:
	@echo "Removing object files"
	@rm -f $(OBJ_DIR)/*.o *.s 

# Default target
all: 8cc

.PHONY: clean cleanobj all self
